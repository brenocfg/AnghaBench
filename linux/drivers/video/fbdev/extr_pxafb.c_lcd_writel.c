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
struct pxafb_info {scalar_t__ mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void
lcd_writel(struct pxafb_info *fbi, unsigned int off, unsigned long val)
{
	__raw_writel(val, fbi->mmio_base + off);
}