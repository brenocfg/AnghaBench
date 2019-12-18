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
typedef  unsigned int u32 ;
struct intel_engine_execlists {scalar_t__* active; } ;
typedef  enum csb_step { ____Placeholder_csb_step } csb_step ;

/* Variables and functions */
 int CSB_COMPLETE ; 
 int CSB_NOP ; 
 int CSB_PREEMPT ; 
 int CSB_PROMOTE ; 
 unsigned int GEN8_CTX_STATUS_IDLE_ACTIVE ; 
 unsigned int GEN8_CTX_STATUS_PREEMPTED ; 

__attribute__((used)) static inline enum csb_step
gen8_csb_parse(const struct intel_engine_execlists *execlists, const u32 *csb)
{
	unsigned int status = *csb;

	if (status & GEN8_CTX_STATUS_IDLE_ACTIVE)
		return CSB_PROMOTE;

	if (status & GEN8_CTX_STATUS_PREEMPTED)
		return CSB_PREEMPT;

	if (*execlists->active)
		return CSB_COMPLETE;

	return CSB_NOP;
}