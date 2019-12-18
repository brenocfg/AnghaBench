#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct cx25821_dev {int _max_num_decoders; int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_AB_DIAG_CTRL ; 
 int /*<<< orphan*/  BYP_AB_CTRL ; 
 int /*<<< orphan*/  DENC_AB_CTRL ; 
 int MAX_DECODERS ; 
 int /*<<< orphan*/  MON_A_CTRL ; 
 int /*<<< orphan*/  PIN_OE_CTRL ; 
 int cx25821_i2c_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int cx25821_i2c_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  medusa_set_decoderduration (struct cx25821_dev*,int,int /*<<< orphan*/ ) ; 
 int medusa_set_videostandard (struct cx25821_dev*) ; 

int medusa_video_init(struct cx25821_dev *dev)
{
	u32 value = 0, tmp = 0;
	int ret_val = 0;
	int i = 0;

	/* disable Auto source selection on all video decoders */
	value = cx25821_i2c_read(&dev->i2c_bus[0], MON_A_CTRL, &tmp);
	value &= 0xFFFFF0FF;
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], MON_A_CTRL, value);

	if (ret_val < 0)
		goto error;

	/* Turn off Master source switch enable */
	value = cx25821_i2c_read(&dev->i2c_bus[0], MON_A_CTRL, &tmp);
	value &= 0xFFFFFFDF;
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], MON_A_CTRL, value);

	if (ret_val < 0)
		goto error;

	/*
	 * FIXME: due to a coding bug the duration was always 0. It's
	 * likely that it really should be something else, but due to the
	 * lack of documentation I have no idea what it should be. For
	 * now just fill in 0 as the duration.
	 */
	for (i = 0; i < dev->_max_num_decoders; i++)
		medusa_set_decoderduration(dev, i, 0);

	/* Select monitor as DENC A input, power up the DAC */
	value = cx25821_i2c_read(&dev->i2c_bus[0], DENC_AB_CTRL, &tmp);
	value &= 0xFF70FF70;
	value |= 0x00090008;	/* set en_active */
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], DENC_AB_CTRL, value);

	if (ret_val < 0)
		goto error;

	/* enable input is VIP/656 */
	value = cx25821_i2c_read(&dev->i2c_bus[0], BYP_AB_CTRL, &tmp);
	value |= 0x00040100;	/* enable VIP */
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], BYP_AB_CTRL, value);

	if (ret_val < 0)
		goto error;

	/* select AFE clock to output mode */
	value = cx25821_i2c_read(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL, &tmp);
	value &= 0x83FFFFFF;
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL,
			value | 0x10000000);

	if (ret_val < 0)
		goto error;

	/* Turn on all of the data out and control output pins. */
	value = cx25821_i2c_read(&dev->i2c_bus[0], PIN_OE_CTRL, &tmp);
	value &= 0xFEF0FE00;
	if (dev->_max_num_decoders == MAX_DECODERS) {
		/*
		 * Note: The octal board does not support control pins(bit16-19)
		 * These bits are ignored in the octal board.
		 *
		 * disable VDEC A-C port, default to Mobilygen Interface
		 */
		value |= 0x010001F8;
	} else {
		/* disable VDEC A-C port, default to Mobilygen Interface */
		value |= 0x010F0108;
	}

	value |= 7;
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], PIN_OE_CTRL, value);

	if (ret_val < 0)
		goto error;

	ret_val = medusa_set_videostandard(dev);

error:
	return ret_val;
}