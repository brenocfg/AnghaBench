#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {unsigned int flags; } ;
struct TYPE_5__ {TYPE_1__ parallel; } ;
struct TYPE_6__ {TYPE_2__ bus; } ;
struct ov5640_dev {TYPE_3__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_IO_MIPI_CTRL00 ; 
 int /*<<< orphan*/  OV5640_REG_PAD_OUTPUT_ENABLE01 ; 
 int /*<<< orphan*/  OV5640_REG_PAD_OUTPUT_ENABLE02 ; 
 int /*<<< orphan*/  OV5640_REG_POLARITY_CTRL00 ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int ov5640_write_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5640_set_stream_dvp(struct ov5640_dev *sensor, bool on)
{
	int ret;
	unsigned int flags = sensor->ep.bus.parallel.flags;
	u8 pclk_pol = 0;
	u8 hsync_pol = 0;
	u8 vsync_pol = 0;

	/*
	 * Note about parallel port configuration.
	 *
	 * When configured in parallel mode, the OV5640 will
	 * output 10 bits data on DVP data lines [9:0].
	 * If only 8 bits data are wanted, the 8 bits data lines
	 * of the camera interface must be physically connected
	 * on the DVP data lines [9:2].
	 *
	 * Control lines polarity can be configured through
	 * devicetree endpoint control lines properties.
	 * If no endpoint control lines properties are set,
	 * polarity will be as below:
	 * - VSYNC:	active high
	 * - HREF:	active low
	 * - PCLK:	active low
	 */

	if (on) {
		/*
		 * configure parallel port control lines polarity
		 *
		 * POLARITY CTRL0
		 * - [5]:	PCLK polarity (0: active low, 1: active high)
		 * - [1]:	HREF polarity (0: active low, 1: active high)
		 * - [0]:	VSYNC polarity (mismatch here between
		 *		datasheet and hardware, 0 is active high
		 *		and 1 is active low...)
		 */
		if (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
			pclk_pol = 1;
		if (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
			hsync_pol = 1;
		if (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			vsync_pol = 1;

		ret = ov5640_write_reg(sensor,
				       OV5640_REG_POLARITY_CTRL00,
				       (pclk_pol << 5) |
				       (hsync_pol << 1) |
				       vsync_pol);

		if (ret)
			return ret;
	}

	/*
	 * powerdown MIPI TX/RX PHY & disable MIPI
	 *
	 * MIPI CONTROL 00
	 * 4:	 PWDN PHY TX
	 * 3:	 PWDN PHY RX
	 * 2:	 MIPI enable
	 */
	ret = ov5640_write_reg(sensor,
			       OV5640_REG_IO_MIPI_CTRL00, on ? 0x18 : 0);
	if (ret)
		return ret;

	/*
	 * enable VSYNC/HREF/PCLK DVP control lines
	 * & D[9:6] DVP data lines
	 *
	 * PAD OUTPUT ENABLE 01
	 * - 6:		VSYNC output enable
	 * - 5:		HREF output enable
	 * - 4:		PCLK output enable
	 * - [3:0]:	D[9:6] output enable
	 */
	ret = ov5640_write_reg(sensor,
			       OV5640_REG_PAD_OUTPUT_ENABLE01,
			       on ? 0x7f : 0);
	if (ret)
		return ret;

	/*
	 * enable D[5:0] DVP data lines
	 *
	 * PAD OUTPUT ENABLE 02
	 * - [7:2]:	D[5:0] output enable
	 */
	return ov5640_write_reg(sensor,
				OV5640_REG_PAD_OUTPUT_ENABLE02,
				on ? 0xfc : 0);
}