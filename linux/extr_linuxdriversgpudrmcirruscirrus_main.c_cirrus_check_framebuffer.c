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
struct TYPE_2__ {int vram_size; } ;
struct cirrus_device {TYPE_1__ mc; } ;

/* Variables and functions */
 int cirrus_bpp ; 

bool cirrus_check_framebuffer(struct cirrus_device *cdev, int width, int height,
			      int bpp, int pitch)
{
	const int max_pitch = 0x1FF << 3; /* (4096 - 1) & ~111b bytes */
	const int max_size = cdev->mc.vram_size;

	if (bpp > cirrus_bpp)
		return false;
	if (bpp > 32)
		return false;

	if (pitch > max_pitch)
		return false;

	if (pitch * height > max_size)
		return false;

	return true;
}