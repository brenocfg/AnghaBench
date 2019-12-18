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
struct hfi1_pportdata {int dummy; } ;
struct hfi1_devdata {int link_credits; int vl15_init; int num_pports; struct hfi1_pportdata* pport; int /*<<< orphan*/  vau; int /*<<< orphan*/  vcu; } ;

/* Variables and functions */
 int CM_GLOBAL_CREDITS ; 
 int /*<<< orphan*/  CM_VAU ; 
 scalar_t__ HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKEY_CHECK ; 
 int /*<<< orphan*/  cu_to_vcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_cu ; 
 int /*<<< orphan*/  init_sc2vl_tables (struct hfi1_devdata*) ; 
 scalar_t__ is_ax (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  set_partition_keys (struct hfi1_pportdata*) ; 
 int vau_to_au (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uninitialized_csrs_and_memories (struct hfi1_devdata*) ; 

__attribute__((used)) static void init_early_variables(struct hfi1_devdata *dd)
{
	int i;

	/* assign link credit variables */
	dd->vau = CM_VAU;
	dd->link_credits = CM_GLOBAL_CREDITS;
	if (is_ax(dd))
		dd->link_credits--;
	dd->vcu = cu_to_vcu(hfi1_cu);
	/* enough room for 8 MAD packets plus header - 17K */
	dd->vl15_init = (8 * (2048 + 128)) / vau_to_au(dd->vau);
	if (dd->vl15_init > dd->link_credits)
		dd->vl15_init = dd->link_credits;

	write_uninitialized_csrs_and_memories(dd);

	if (HFI1_CAP_IS_KSET(PKEY_CHECK))
		for (i = 0; i < dd->num_pports; i++) {
			struct hfi1_pportdata *ppd = &dd->pport[i];

			set_partition_keys(ppd);
		}
	init_sc2vl_tables(dd);
}