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
struct ocm_info {int /*<<< orphan*/  c; int /*<<< orphan*/  nc; int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 int ocm_count ; 
 scalar_t__ ocm_free_region (int /*<<< orphan*/ *,void const*) ; 
 struct ocm_info* ocm_get_node (int) ; 

void ppc4xx_ocm_free(const void *addr)
{
	int i;

	if (!addr)
		return;

	for (i = 0; i < ocm_count; i++) {
		struct ocm_info *ocm = ocm_get_node(i);

		if (!ocm || !ocm->ready)
			continue;

		if (ocm_free_region(&ocm->nc, addr) ||
			ocm_free_region(&ocm->c, addr))
			return;
	}
}