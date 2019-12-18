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
struct irt_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct irt_entry *iosapic_alloc_irt(int num_entries)
{
	unsigned long a;

	/* The IRT needs to be 8-byte aligned for the PDC call. 
	 * Normally kmalloc would guarantee larger alignment, but
	 * if CONFIG_DEBUG_SLAB is enabled, then we can get only
	 * 4-byte alignment on 32-bit kernels
	 */
	a = (unsigned long)kmalloc(sizeof(struct irt_entry) * num_entries + 8, GFP_KERNEL);
	a = (a + 7UL) & ~7UL;
	return (struct irt_entry *)a;
}