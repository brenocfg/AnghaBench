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
struct pmb_entry {scalar_t__ vpn; scalar_t__ size; scalar_t__ ppn; scalar_t__ flags; } ;

/* Variables and functions */

__attribute__((used)) static inline bool pmb_can_merge(struct pmb_entry *a, struct pmb_entry *b)
{
	return (b->vpn == (a->vpn + a->size)) &&
	       (b->ppn == (a->ppn + a->size)) &&
	       (b->flags == a->flags);
}