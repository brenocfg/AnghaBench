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
typedef  int u64 ;
struct TYPE_2__ {int addressing_mode; } ;
struct intel_vgpu_workload {TYPE_1__ ctx_desc; } ;
struct intel_context {int lrc_desc; } ;

/* Variables and functions */
 int GEN8_CTX_ADDRESSING_MODE_SHIFT ; 

__attribute__((used)) static void
shadow_context_descriptor_update(struct intel_context *ce,
				 struct intel_vgpu_workload *workload)
{
	u64 desc = ce->lrc_desc;

	/*
	 * Update bits 0-11 of the context descriptor which includes flags
	 * like GEN8_CTX_* cached in desc_template
	 */
	desc &= ~(0x3 << GEN8_CTX_ADDRESSING_MODE_SHIFT);
	desc |= workload->ctx_desc.addressing_mode <<
		GEN8_CTX_ADDRESSING_MODE_SHIFT;

	ce->lrc_desc = desc;
}