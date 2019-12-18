#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct intel_uncore {int dummy; } ;
struct intel_guc {int dummy; } ;
struct TYPE_2__ {struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEN8_DRBREGL (scalar_t__) ; 
 int GEN8_DRB_VALID ; 
 scalar_t__ GUC_NUM_DOORBELLS ; 
 TYPE_1__* guc_to_gt (struct intel_guc*) ; 
 int intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __doorbell_valid(struct intel_guc *guc, u16 db_id)
{
	struct intel_uncore *uncore = guc_to_gt(guc)->uncore;

	GEM_BUG_ON(db_id >= GUC_NUM_DOORBELLS);
	return intel_uncore_read(uncore, GEN8_DRBREGL(db_id)) & GEN8_DRB_VALID;
}