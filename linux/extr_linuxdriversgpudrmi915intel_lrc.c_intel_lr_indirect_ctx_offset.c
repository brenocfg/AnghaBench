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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN10_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT ; 
 int /*<<< orphan*/  GEN11_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT ; 
 int /*<<< orphan*/  GEN8_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT ; 
 int /*<<< orphan*/  GEN9_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static u32 intel_lr_indirect_ctx_offset(struct intel_engine_cs *engine)
{
	u32 indirect_ctx_offset;

	switch (INTEL_GEN(engine->i915)) {
	default:
		MISSING_CASE(INTEL_GEN(engine->i915));
		/* fall through */
	case 11:
		indirect_ctx_offset =
			GEN11_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT;
		break;
	case 10:
		indirect_ctx_offset =
			GEN10_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT;
		break;
	case 9:
		indirect_ctx_offset =
			GEN9_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT;
		break;
	case 8:
		indirect_ctx_offset =
			GEN8_CTX_RCS_INDIRECT_CTX_OFFSET_DEFAULT;
		break;
	}

	return indirect_ctx_offset;
}