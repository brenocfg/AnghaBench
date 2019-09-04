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
struct ns83820 {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CR ; 
 int /*<<< orphan*/  Dprintk (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ns83820_do_reset(struct ns83820 *dev, u32 which)
{
	Dprintk("resetting chip...\n");
	writel(which, dev->base + CR);
	do {
		schedule();
	} while (readl(dev->base + CR) & which);
	Dprintk("okay!\n");
}