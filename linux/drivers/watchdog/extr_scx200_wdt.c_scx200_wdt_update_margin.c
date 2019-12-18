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

/* Variables and functions */
 int W_SCALE ; 
 int margin ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int wdto_restart ; 

__attribute__((used)) static void scx200_wdt_update_margin(void)
{
	pr_info("timer margin %d seconds\n", margin);
	wdto_restart = margin * W_SCALE;
}