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
struct fb_wid_list {int wl_count; struct fb_wid_item* wl_list; } ;
struct fb_wid_item {int wi_index; int* wi_values; int /*<<< orphan*/  wi_type; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_WID_DBL_24 ; 
 int /*<<< orphan*/  FB_WID_DBL_8 ; 
 int /*<<< orphan*/  leo_wid_put (struct fb_info*,struct fb_wid_list*) ; 

__attribute__((used)) static void leo_init_wids(struct fb_info *info)
{
	struct fb_wid_item wi;
	struct fb_wid_list wl;

	wl.wl_count = 1;
	wl.wl_list = &wi;
	wi.wi_type = FB_WID_DBL_8;
	wi.wi_index = 0;
	wi.wi_values [0] = 0x2c0;
	leo_wid_put(info, &wl);
	wi.wi_index = 1;
	wi.wi_values [0] = 0x30;
	leo_wid_put(info, &wl);
	wi.wi_index = 2;
	wi.wi_values [0] = 0x20;
	leo_wid_put(info, &wl);
	wi.wi_type = FB_WID_DBL_24;
	wi.wi_index = 1;
	wi.wi_values [0] = 0x30;
	leo_wid_put(info, &wl);
}