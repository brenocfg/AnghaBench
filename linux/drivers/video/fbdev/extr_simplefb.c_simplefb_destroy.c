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
struct fb_info {scalar_t__ screen_base; int /*<<< orphan*/  par; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  simplefb_clocks_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplefb_regulators_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void simplefb_destroy(struct fb_info *info)
{
	simplefb_regulators_destroy(info->par);
	simplefb_clocks_destroy(info->par);
	if (info->screen_base)
		iounmap(info->screen_base);
}