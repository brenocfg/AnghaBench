#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hst_mode; } ;
struct cyttsp {int /*<<< orphan*/  irq; TYPE_1__ xy_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_REG_BASE ; 
 int EIO ; 
 scalar_t__ GET_HSTMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int ttsp_read_block_data (struct cyttsp*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static int cyttsp_enable(struct cyttsp *ts)
{
	int error;

	/*
	 * The device firmware can wake on an I2C or SPI memory slave
	 * address match. So just reading a register is sufficient to
	 * wake up the device. The first read attempt will fail but it
	 * will wake it up making the second read attempt successful.
	 */
	error = ttsp_read_block_data(ts, CY_REG_BASE,
				     sizeof(ts->xy_data), &ts->xy_data);
	if (error)
		return error;

	if (GET_HSTMODE(ts->xy_data.hst_mode))
		return -EIO;

	enable_irq(ts->irq);

	return 0;
}