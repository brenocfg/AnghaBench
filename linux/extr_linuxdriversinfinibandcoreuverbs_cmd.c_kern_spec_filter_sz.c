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
struct ib_uverbs_flow_spec_hdr {int size; } ;

/* Variables and functions */

__attribute__((used)) static size_t kern_spec_filter_sz(const struct ib_uverbs_flow_spec_hdr *spec)
{
	/* Returns user space filter size, includes padding */
	return (spec->size - sizeof(struct ib_uverbs_flow_spec_hdr)) / 2;
}