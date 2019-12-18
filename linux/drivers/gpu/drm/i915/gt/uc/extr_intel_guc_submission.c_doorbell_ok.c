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
struct intel_guc {int /*<<< orphan*/  doorbell_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GUC_NUM_DOORBELLS ; 
 int __doorbell_valid (struct intel_guc*,scalar_t__) ; 
 int test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static bool doorbell_ok(struct intel_guc *guc, u16 db_id)
{
	bool valid;

	GEM_BUG_ON(db_id >= GUC_NUM_DOORBELLS);

	valid = __doorbell_valid(guc, db_id);

	if (test_bit(db_id, guc->doorbell_bitmap) == valid)
		return true;

	DRM_DEBUG_DRIVER("Doorbell %u has unexpected state: valid=%s\n",
			 db_id, yesno(valid));

	return false;
}