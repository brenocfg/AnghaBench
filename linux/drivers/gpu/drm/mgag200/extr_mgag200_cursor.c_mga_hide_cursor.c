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
struct TYPE_2__ {int /*<<< orphan*/ * pixels_current; } ;
struct mga_device {TYPE_1__ cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGA_CURPOSXH ; 
 int /*<<< orphan*/  MGA_CURPOSXL ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mga_hide_cursor(struct mga_device *mdev)
{
	WREG8(MGA_CURPOSXL, 0);
	WREG8(MGA_CURPOSXH, 0);
	if (mdev->cursor.pixels_current)
		drm_gem_vram_unpin(mdev->cursor.pixels_current);
	mdev->cursor.pixels_current = NULL;
}