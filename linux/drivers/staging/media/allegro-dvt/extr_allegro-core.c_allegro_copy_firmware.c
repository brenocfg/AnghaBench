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
typedef  int /*<<< orphan*/  u8 ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  sram; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const* const,size_t) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void allegro_copy_firmware(struct allegro_dev *dev,
				  const u8 * const buf, size_t size)
{
	int err = 0;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "copy mcu firmware (%zu B) to SRAM\n", size);
	err = regmap_bulk_write(dev->sram, 0x0, buf, size / 4);
	if (err)
		v4l2_err(&dev->v4l2_dev,
			 "failed to copy firmware: %d\n", err);
}