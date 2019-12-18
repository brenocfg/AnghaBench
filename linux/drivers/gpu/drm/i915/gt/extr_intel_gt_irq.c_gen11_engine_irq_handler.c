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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct intel_gt {struct intel_engine_cs*** engine_class; } ;
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 size_t const MAX_ENGINE_INSTANCE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,size_t const,size_t const) ; 
 void cs_irq_handler (struct intel_engine_cs*,int /*<<< orphan*/  const) ; 
 scalar_t__ likely (struct intel_engine_cs*) ; 

__attribute__((used)) static void
gen11_engine_irq_handler(struct intel_gt *gt, const u8 class,
			 const u8 instance, const u16 iir)
{
	struct intel_engine_cs *engine;

	if (instance <= MAX_ENGINE_INSTANCE)
		engine = gt->engine_class[class][instance];
	else
		engine = NULL;

	if (likely(engine))
		return cs_irq_handler(engine, iir);

	WARN_ONCE(1, "unhandled engine interrupt class=0x%x, instance=0x%x\n",
		  class, instance);
}