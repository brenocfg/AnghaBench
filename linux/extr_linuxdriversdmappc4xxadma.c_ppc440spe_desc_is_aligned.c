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
struct ppc440spe_adma_desc_slot {int idx; } ;

/* Variables and functions */

__attribute__((used)) static inline int ppc440spe_desc_is_aligned(
	struct ppc440spe_adma_desc_slot *desc, int num_slots)
{
	return (desc->idx & (num_slots - 1)) ? 0 : 1;
}