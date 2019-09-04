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
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ FAB_SF_MODE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ fabric ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void hip04_set_snoop_filter(unsigned int cluster, unsigned int on)
{
	unsigned long data;

	if (!fabric)
		BUG();
	data = readl_relaxed(fabric + FAB_SF_MODE);
	if (on)
		data |= 1 << cluster;
	else
		data &= ~(1 << cluster);
	writel_relaxed(data, fabric + FAB_SF_MODE);
	do {
		cpu_relax();
	} while (data != readl_relaxed(fabric + FAB_SF_MODE));
}