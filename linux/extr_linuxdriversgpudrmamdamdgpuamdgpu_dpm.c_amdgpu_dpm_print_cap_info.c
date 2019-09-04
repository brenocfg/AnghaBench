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
 int ATOM_PPLIB_DISALLOW_ON_DC ; 
 int ATOM_PPLIB_SINGLE_DISPLAY_ONLY ; 
 int ATOM_PPLIB_SUPPORTS_VIDEO_PLAYBACK ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  printk (char*) ; 

void amdgpu_dpm_print_cap_info(u32 caps)
{
	printk("\tcaps:");
	if (caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY)
		pr_cont(" single_disp");
	if (caps & ATOM_PPLIB_SUPPORTS_VIDEO_PLAYBACK)
		pr_cont(" video");
	if (caps & ATOM_PPLIB_DISALLOW_ON_DC)
		pr_cont(" no_dc");
	pr_cont("\n");
}