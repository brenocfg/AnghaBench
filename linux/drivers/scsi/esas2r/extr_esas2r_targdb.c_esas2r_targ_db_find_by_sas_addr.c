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
typedef  scalar_t__ u64 ;
struct esas2r_target {scalar_t__ sas_addr; } ;
struct esas2r_adapter {struct esas2r_target* targetdb_end; struct esas2r_target* targetdb; } ;

/* Variables and functions */

struct esas2r_target *esas2r_targ_db_find_by_sas_addr(struct esas2r_adapter *a,
						      u64 *sas_addr)
{
	struct esas2r_target *t;

	for (t = a->targetdb; t < a->targetdb_end; t++)
		if (t->sas_addr == *sas_addr)
			return t;

	return NULL;
}