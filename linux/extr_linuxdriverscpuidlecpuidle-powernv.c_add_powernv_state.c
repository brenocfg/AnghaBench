#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_4__ {unsigned int flags; unsigned int target_residency; unsigned int exit_latency; int (* enter ) (struct cpuidle_device*,struct cpuidle_driver*,int) ;int /*<<< orphan*/  desc; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {void* mask; void* val; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUIDLE_NAME_LEN ; 
 TYPE_2__* powernv_states ; 
 TYPE_1__* stop_psscr_table ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void add_powernv_state(int index, const char *name,
				     unsigned int flags,
				     int (*idle_fn)(struct cpuidle_device *,
						    struct cpuidle_driver *,
						    int),
				     unsigned int target_residency,
				     unsigned int exit_latency,
				     u64 psscr_val, u64 psscr_mask)
{
	strlcpy(powernv_states[index].name, name, CPUIDLE_NAME_LEN);
	strlcpy(powernv_states[index].desc, name, CPUIDLE_NAME_LEN);
	powernv_states[index].flags = flags;
	powernv_states[index].target_residency = target_residency;
	powernv_states[index].exit_latency = exit_latency;
	powernv_states[index].enter = idle_fn;
	/* For power8 and below psscr_* will be 0 */
	stop_psscr_table[index].val = psscr_val;
	stop_psscr_table[index].mask = psscr_mask;
}