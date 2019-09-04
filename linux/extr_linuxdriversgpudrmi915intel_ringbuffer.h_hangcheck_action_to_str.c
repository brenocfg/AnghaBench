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
typedef  enum intel_engine_hangcheck_action { ____Placeholder_intel_engine_hangcheck_action } intel_engine_hangcheck_action ;

/* Variables and functions */
#define  ENGINE_ACTIVE_HEAD 134 
#define  ENGINE_ACTIVE_SEQNO 133 
#define  ENGINE_ACTIVE_SUBUNITS 132 
#define  ENGINE_DEAD 131 
#define  ENGINE_IDLE 130 
#define  ENGINE_WAIT 129 
#define  ENGINE_WAIT_KICK 128 

__attribute__((used)) static inline const char *
hangcheck_action_to_str(const enum intel_engine_hangcheck_action a)
{
	switch (a) {
	case ENGINE_IDLE:
		return "idle";
	case ENGINE_WAIT:
		return "wait";
	case ENGINE_ACTIVE_SEQNO:
		return "active seqno";
	case ENGINE_ACTIVE_HEAD:
		return "active head";
	case ENGINE_ACTIVE_SUBUNITS:
		return "active subunits";
	case ENGINE_WAIT_KICK:
		return "wait kick";
	case ENGINE_DEAD:
		return "dead";
	}

	return "unknown";
}