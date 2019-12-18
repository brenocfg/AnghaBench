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
struct pvr2fb_par {scalar_t__ mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void pvr2fb_set_pal_entry(struct pvr2fb_par *par,
					unsigned int regno,
					unsigned int val)
{
	fb_writel(val, par->mmio_base + 0x1000 + (4 * regno));
}