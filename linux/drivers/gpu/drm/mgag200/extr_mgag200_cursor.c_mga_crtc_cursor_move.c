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
struct mga_device {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MGA_CURPOSXH ; 
 int /*<<< orphan*/  MGA_CURPOSXL ; 
 int /*<<< orphan*/  MGA_CURPOSYH ; 
 int /*<<< orphan*/  MGA_CURPOSYL ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 

int mga_crtc_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct mga_device *mdev = (struct mga_device *)crtc->dev->dev_private;
	/* Our origin is at (64,64) */
	x += 64;
	y += 64;

	BUG_ON(x <= 0);
	BUG_ON(y <= 0);
	BUG_ON(x & ~0xffff);
	BUG_ON(y & ~0xffff);

	WREG8(MGA_CURPOSXL, x & 0xff);
	WREG8(MGA_CURPOSXH, (x>>8) & 0xff);

	WREG8(MGA_CURPOSYL, y & 0xff);
	WREG8(MGA_CURPOSYH, (y>>8) & 0xff);
	return 0;
}