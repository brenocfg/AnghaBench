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
struct intel_context {int lrc_desc; TYPE_1__* gem_context; } ;
struct TYPE_2__ {unsigned long long desc_template; } ;

/* Variables and functions */
 int U64_MAX ; 

__attribute__((used)) static void shadow_context_descriptor_update(struct intel_context *ce)
{
	u64 desc = 0;

	desc = ce->lrc_desc;

	/* Update bits 0-11 of the context descriptor which includes flags
	 * like GEN8_CTX_* cached in desc_template
	 */
	desc &= U64_MAX << 12;
	desc |= ce->gem_context->desc_template & ((1ULL << 12) - 1);

	ce->lrc_desc = desc;
}