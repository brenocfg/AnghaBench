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
struct enetc_bdr {scalar_t__ next_to_clean; scalar_t__ next_to_use; int bd_count; } ;

/* Variables and functions */

__attribute__((used)) static inline int enetc_bd_unused(struct enetc_bdr *bdr)
{
	if (bdr->next_to_clean > bdr->next_to_use)
		return bdr->next_to_clean - bdr->next_to_use - 1;

	return bdr->bd_count + bdr->next_to_clean - bdr->next_to_use - 1;
}