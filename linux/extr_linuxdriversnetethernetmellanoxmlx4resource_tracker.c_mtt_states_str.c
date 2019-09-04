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
typedef  enum res_mtt_states { ____Placeholder_res_mtt_states } res_mtt_states ;

/* Variables and functions */
#define  RES_MTT_ALLOCATED 129 
#define  RES_MTT_BUSY 128 

__attribute__((used)) static inline const char *mtt_states_str(enum res_mtt_states state)
{
	switch (state) {
	case RES_MTT_BUSY: return "RES_MTT_BUSY";
	case RES_MTT_ALLOCATED: return "RES_MTT_ALLOCATED";
	default: return "Unknown";
	}
}