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
struct pvr2fb_par {int dummy; } ;

/* Variables and functions */
 unsigned long BLANK_BIT ; 
 int /*<<< orphan*/  DISP_DIWCONF ; 
 struct pvr2fb_par* currentpar ; 
 scalar_t__ do_blank ; 
 unsigned long fb_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_writel (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ is_blanked ; 

__attribute__((used)) static void pvr2_do_blank(void)
{
	struct pvr2fb_par *par = currentpar;
	unsigned long diwconf;

	diwconf = fb_readl(DISP_DIWCONF);
	if (do_blank > 0)
		fb_writel(diwconf | BLANK_BIT, DISP_DIWCONF);
	else
		fb_writel(diwconf & ~BLANK_BIT, DISP_DIWCONF);

	is_blanked = do_blank > 0 ? do_blank : 0;
}