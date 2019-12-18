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
 struct fb_info** _au1200fb_infos ; 
 int device_count ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int fbinfo2index (struct fb_info *fb_info)
{
	int i;

	for (i = 0; i < device_count; ++i) {
		if (fb_info == _au1200fb_infos[i])
			return i;
	}
	printk("au1200fb: ERROR: fbinfo2index failed!\n");
	return -1;
}