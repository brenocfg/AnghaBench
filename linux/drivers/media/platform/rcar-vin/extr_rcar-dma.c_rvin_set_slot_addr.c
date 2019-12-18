#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rvin_video_format {int bpp; } ;
struct TYPE_3__ {int bytesperline; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {int left; int top; } ;
struct rvin_dev {TYPE_1__ format; TYPE_2__ compose; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int HW_BUFFER_MASK ; 
 int /*<<< orphan*/  VNMB_REG (int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct rvin_video_format* rvin_format_from_pixel (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvin_set_slot_addr(struct rvin_dev *vin, int slot, dma_addr_t addr)
{
	const struct rvin_video_format *fmt;
	int offsetx, offsety;
	dma_addr_t offset;

	fmt = rvin_format_from_pixel(vin, vin->format.pixelformat);

	/*
	 * There is no HW support for composition do the beast we can
	 * by modifying the buffer offset
	 */
	offsetx = vin->compose.left * fmt->bpp;
	offsety = vin->compose.top * vin->format.bytesperline;
	offset = addr + offsetx + offsety;

	/*
	 * The address needs to be 128 bytes aligned. Driver should never accept
	 * settings that do not satisfy this in the first place...
	 */
	if (WARN_ON((offsetx | offsety | offset) & HW_BUFFER_MASK))
		return;

	rvin_write(vin, offset, VNMB_REG(slot));
}