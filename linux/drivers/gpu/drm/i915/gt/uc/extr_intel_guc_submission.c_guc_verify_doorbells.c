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
typedef  scalar_t__ u16 ;
struct intel_guc {int dummy; } ;

/* Variables and functions */
 scalar_t__ GUC_NUM_DOORBELLS ; 
 int /*<<< orphan*/  doorbell_ok (struct intel_guc*,scalar_t__) ; 

__attribute__((used)) static bool guc_verify_doorbells(struct intel_guc *guc)
{
	bool doorbells_ok = true;
	u16 db_id;

	for (db_id = 0; db_id < GUC_NUM_DOORBELLS; ++db_id)
		if (!doorbell_ok(guc, db_id))
			doorbells_ok = false;

	return doorbells_ok;
}