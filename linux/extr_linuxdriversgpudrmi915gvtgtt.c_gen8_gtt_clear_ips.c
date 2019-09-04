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
struct intel_gvt_gtt_entry {scalar_t__ type; int /*<<< orphan*/  val64; } ;

/* Variables and functions */
 scalar_t__ GEM_WARN_ON (int) ; 
 int /*<<< orphan*/  GEN8_PDE_IPS_64K ; 
 scalar_t__ GTT_TYPE_PPGTT_PDE_ENTRY ; 

__attribute__((used)) static void gen8_gtt_clear_ips(struct intel_gvt_gtt_entry *e)
{
	if (GEM_WARN_ON(e->type != GTT_TYPE_PPGTT_PDE_ENTRY))
		return;

	e->val64 &= ~GEN8_PDE_IPS_64K;
}