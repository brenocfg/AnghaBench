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
struct enetc_cbdr {int next_to_clean; int next_to_use; int bd_count; } ;

/* Variables and functions */

__attribute__((used)) static int enetc_cbd_unused(struct enetc_cbdr *r)
{
	return (r->next_to_clean - r->next_to_use - 1 + r->bd_count) %
		r->bd_count;
}