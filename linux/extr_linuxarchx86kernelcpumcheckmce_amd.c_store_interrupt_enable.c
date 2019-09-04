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
typedef  int /*<<< orphan*/  tr ;
struct threshold_block {int interrupt_enable; int /*<<< orphan*/  cpu; int /*<<< orphan*/  interrupt_capable; } ;
struct thresh_restart {struct threshold_block* b; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  memset (struct thresh_restart*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thresh_restart*,int) ; 
 int /*<<< orphan*/  threshold_restart_bank ; 

__attribute__((used)) static ssize_t
store_interrupt_enable(struct threshold_block *b, const char *buf, size_t size)
{
	struct thresh_restart tr;
	unsigned long new;

	if (!b->interrupt_capable)
		return -EINVAL;

	if (kstrtoul(buf, 0, &new) < 0)
		return -EINVAL;

	b->interrupt_enable = !!new;

	memset(&tr, 0, sizeof(tr));
	tr.b		= b;

	smp_call_function_single(b->cpu, threshold_restart_bank, &tr, 1);

	return size;
}