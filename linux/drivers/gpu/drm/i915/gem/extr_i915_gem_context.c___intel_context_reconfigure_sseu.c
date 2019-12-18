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
struct intel_sseu {int dummy; } ;
struct intel_context {struct intel_sseu sseu; TYPE_1__* engine; } ;
typedef  int /*<<< orphan*/  sseu ;
struct TYPE_2__ {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int gen8_modify_rpcs (struct intel_context*,struct intel_sseu) ; 
 int intel_context_lock_pinned (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_unlock_pinned (struct intel_context*) ; 
 int /*<<< orphan*/  memcmp (struct intel_sseu*,struct intel_sseu*,int) ; 

__attribute__((used)) static int
__intel_context_reconfigure_sseu(struct intel_context *ce,
				 struct intel_sseu sseu)
{
	int ret;

	GEM_BUG_ON(INTEL_GEN(ce->engine->i915) < 8);

	ret = intel_context_lock_pinned(ce);
	if (ret)
		return ret;

	/* Nothing to do if unmodified. */
	if (!memcmp(&ce->sseu, &sseu, sizeof(sseu)))
		goto unlock;

	ret = gen8_modify_rpcs(ce, sseu);
	if (!ret)
		ce->sseu = sseu;

unlock:
	intel_context_unlock_pinned(ce);
	return ret;
}