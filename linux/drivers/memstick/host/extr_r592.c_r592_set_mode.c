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
struct r592_device {int parallel_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  R592_IO ; 
 int /*<<< orphan*/  R592_IO_MODE ; 
 int /*<<< orphan*/  R592_IO_MODE_PARALLEL ; 
 int /*<<< orphan*/  R592_IO_MODE_SERIAL ; 
 int R592_IO_SERIAL1 ; 
 int R592_IO_SERIAL2 ; 
 int /*<<< orphan*/  R592_POWER ; 
 int R592_POWER_20 ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  r592_clear_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r592_set_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r592_write_reg (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r592_set_mode(struct r592_device *dev, bool parallel_mode)
{
	if (!parallel_mode) {
		dbg("switching to serial mode");

		/* Set serial mode */
		r592_write_reg(dev, R592_IO_MODE, R592_IO_MODE_SERIAL);

		r592_clear_reg_mask(dev, R592_POWER, R592_POWER_20);

	} else {
		dbg("switching to parallel mode");

		/* This setting should be set _before_ switch TPC */
		r592_set_reg_mask(dev, R592_POWER, R592_POWER_20);

		r592_clear_reg_mask(dev, R592_IO,
			R592_IO_SERIAL1 | R592_IO_SERIAL2);

		/* Set the parallel mode now */
		r592_write_reg(dev, R592_IO_MODE, R592_IO_MODE_PARALLEL);
	}

	dev->parallel_mode = parallel_mode;
	return 0;
}