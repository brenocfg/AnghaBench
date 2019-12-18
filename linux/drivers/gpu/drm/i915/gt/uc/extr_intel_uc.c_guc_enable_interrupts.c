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
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct intel_guc*) ;} ;
struct intel_guc {TYPE_1__ interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct intel_guc*) ; 

__attribute__((used)) static void guc_enable_interrupts(struct intel_guc *guc)
{
	guc->interrupts.enable(guc);
}