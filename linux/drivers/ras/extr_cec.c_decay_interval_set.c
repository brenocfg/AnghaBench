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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ CEC_DECAY_MAX_INTERVAL ; 
 scalar_t__ CEC_DECAY_MIN_INTERVAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  cec_mod_work (scalar_t__) ; 
 scalar_t__ decay_interval ; 

__attribute__((used)) static int decay_interval_set(void *data, u64 val)
{
	if (val < CEC_DECAY_MIN_INTERVAL)
		return -EINVAL;

	if (val > CEC_DECAY_MAX_INTERVAL)
		return -EINVAL;

	*(u64 *)data   = val;
	decay_interval = val;

	cec_mod_work(decay_interval);

	return 0;
}