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
struct TYPE_3__ {TYPE_2__* pixels_2; TYPE_2__* pixels_1; } ;
struct mga_device {TYPE_1__ cursor; } ;
struct TYPE_4__ {scalar_t__ pin_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGA_CURPOSXH ; 
 int /*<<< orphan*/  MGA_CURPOSXL ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgag200_bo_unpin (TYPE_2__*) ; 

__attribute__((used)) static void mga_hide_cursor(struct mga_device *mdev)
{
	WREG8(MGA_CURPOSXL, 0);
	WREG8(MGA_CURPOSXH, 0);
	if (mdev->cursor.pixels_1->pin_count)
		mgag200_bo_unpin(mdev->cursor.pixels_1);
	if (mdev->cursor.pixels_2->pin_count)
		mgag200_bo_unpin(mdev->cursor.pixels_2);
}