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
struct context_entry {int hi; } ;

/* Variables and functions */

__attribute__((used)) static inline int context_domain_id(struct context_entry *c)
{
	return((c->hi >> 8) & 0xffff);
}