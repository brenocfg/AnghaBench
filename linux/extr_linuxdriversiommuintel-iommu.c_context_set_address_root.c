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
struct context_entry {unsigned long lo; } ;

/* Variables and functions */
 unsigned long VTD_PAGE_MASK ; 

__attribute__((used)) static inline void context_set_address_root(struct context_entry *context,
					    unsigned long value)
{
	context->lo &= ~VTD_PAGE_MASK;
	context->lo |= value & VTD_PAGE_MASK;
}