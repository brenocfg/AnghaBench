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
struct fb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int matroxfb_dh_blank(int blank, struct fb_info* info) {
#define m2info (container_of(info, struct matroxfb_dh_fb_info, fbcon))
	switch (blank) {
		case 1:
		case 2:
		case 3:
		case 4:
		default:;
	}
	/* do something... */
	return 0;
#undef m2info
}