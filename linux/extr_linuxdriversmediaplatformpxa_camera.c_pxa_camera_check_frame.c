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

/* Variables and functions */

__attribute__((used)) static int pxa_camera_check_frame(u32 width, u32 height)
{
	/* limit to pxa hardware capabilities */
	return height < 32 || height > 2048 || width < 48 || width > 2048 ||
		(width & 0x01);
}