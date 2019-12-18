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
typedef  int u16 ;
struct intel_guc {int dummy; } ;

/* Variables and functions */
 int GUC_INTR_GUC2HOST ; 
 int /*<<< orphan*/  intel_guc_to_host_event_handler (struct intel_guc*) ; 

__attribute__((used)) static void guc_irq_handler(struct intel_guc *guc, u16 iir)
{
	if (iir & GUC_INTR_GUC2HOST)
		intel_guc_to_host_event_handler(guc);
}