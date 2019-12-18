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
typedef  enum nvme_ana_state { ____Placeholder_nvme_ana_state } nvme_ana_state ;

/* Variables and functions */
 int NVME_ANA_NONOPTIMIZED ; 
 int NVME_ANA_OPTIMIZED ; 

__attribute__((used)) static inline bool nvme_state_is_live(enum nvme_ana_state state)
{
	return state == NVME_ANA_OPTIMIZED || state == NVME_ANA_NONOPTIMIZED;
}