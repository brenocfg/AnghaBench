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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 int MIN_OSCR_DELTA ; 
 int /*<<< orphan*/  OST_OIER ; 
 unsigned long OST_OIER_E0 ; 
 int /*<<< orphan*/  OST_OSCR ; 
 int /*<<< orphan*/  OST_OSMR0 ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
puv3_osmr0_set_next_event(unsigned long delta, struct clock_event_device *c)
{
	unsigned long next, oscr;

	writel(readl(OST_OIER) | OST_OIER_E0, OST_OIER);
	next = readl(OST_OSCR) + delta;
	writel(next, OST_OSMR0);
	oscr = readl(OST_OSCR);

	return (signed)(next - oscr) <= MIN_OSCR_DELTA ? -ETIME : 0;
}