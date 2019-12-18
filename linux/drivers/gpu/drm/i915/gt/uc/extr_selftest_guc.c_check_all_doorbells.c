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
 int EIO ; 
 scalar_t__ GUC_NUM_DOORBELLS ; 
 int /*<<< orphan*/  doorbell_ok (struct intel_guc*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info_once (char*,scalar_t__) ; 

__attribute__((used)) static int check_all_doorbells(struct intel_guc *guc)
{
	u16 db_id;

	pr_info_once("Max number of doorbells: %d", GUC_NUM_DOORBELLS);
	for (db_id = 0; db_id < GUC_NUM_DOORBELLS; ++db_id) {
		if (!doorbell_ok(guc, db_id)) {
			pr_err("doorbell %d, not ok\n", db_id);
			return -EIO;
		}
	}

	return 0;
}