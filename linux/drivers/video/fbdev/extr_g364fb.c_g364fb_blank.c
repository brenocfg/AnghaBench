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
 scalar_t__ CTLA_REG ; 
 unsigned int FORCE_BLANK ; 

__attribute__((used)) static int g364fb_blank(int blank, struct fb_info *info)
{
	if (blank)
		*(unsigned int *) CTLA_REG |= FORCE_BLANK;
	else
		*(unsigned int *) CTLA_REG &= ~FORCE_BLANK;
	return 0;
}