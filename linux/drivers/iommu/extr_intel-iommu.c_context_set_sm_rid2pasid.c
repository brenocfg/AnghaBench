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
struct context_entry {unsigned long hi; } ;

/* Variables and functions */

__attribute__((used)) static inline void
context_set_sm_rid2pasid(struct context_entry *context, unsigned long pasid)
{
	context->hi |= pasid & ((1 << 20) - 1);
	context->hi |= (1 << 20);
}