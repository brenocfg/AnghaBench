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
struct intel_guc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOFT_SCRATCH (int) ; 
 TYPE_1__* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uncore_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void guc_clear_mmio_msg(struct intel_guc *guc)
{
	intel_uncore_write(guc_to_gt(guc)->uncore, SOFT_SCRATCH(15), 0);
}