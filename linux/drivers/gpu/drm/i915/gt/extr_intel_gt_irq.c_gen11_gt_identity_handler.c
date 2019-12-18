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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct intel_gt {int dummy; } ;

/* Variables and functions */
 scalar_t__ const COPY_ENGINE_CLASS ; 
 scalar_t__ GEN11_INTR_ENGINE_CLASS (int /*<<< orphan*/  const) ; 
 scalar_t__ GEN11_INTR_ENGINE_INSTANCE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  GEN11_INTR_ENGINE_INTR (int /*<<< orphan*/  const) ; 
 scalar_t__ const OTHER_CLASS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__ const,scalar_t__ const,int /*<<< orphan*/  const) ; 
 void gen11_engine_irq_handler (struct intel_gt*,scalar_t__ const,scalar_t__ const,int /*<<< orphan*/  const) ; 
 void gen11_other_irq_handler (struct intel_gt*,scalar_t__ const,int /*<<< orphan*/  const) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
gen11_gt_identity_handler(struct intel_gt *gt, const u32 identity)
{
	const u8 class = GEN11_INTR_ENGINE_CLASS(identity);
	const u8 instance = GEN11_INTR_ENGINE_INSTANCE(identity);
	const u16 intr = GEN11_INTR_ENGINE_INTR(identity);

	if (unlikely(!intr))
		return;

	if (class <= COPY_ENGINE_CLASS)
		return gen11_engine_irq_handler(gt, class, instance, intr);

	if (class == OTHER_CLASS)
		return gen11_other_irq_handler(gt, instance, intr);

	WARN_ONCE(1, "unknown interrupt class=0x%x, instance=0x%x, intr=0x%x\n",
		  class, instance, intr);
}