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
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GEM_HWS_INDEX ; 
 int /*<<< orphan*/  intel_engine_wakeup (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_write_status_page (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mock_seqno_advance(struct intel_engine_cs *engine, u32 seqno)
{
	intel_write_status_page(engine, I915_GEM_HWS_INDEX, seqno);
	intel_engine_wakeup(engine);
}