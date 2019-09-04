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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {TYPE_2__* channels; int /*<<< orphan*/  lock; } ;
struct kvm_pit {TYPE_1__ pit_state; } ;
struct TYPE_4__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pit_load_count (struct kvm_pit*,int,int /*<<< orphan*/ ) ; 

void kvm_pit_load_count(struct kvm_pit *pit, int channel, u32 val,
		int hpet_legacy_start)
{
	u8 saved_mode;

	WARN_ON_ONCE(!mutex_is_locked(&pit->pit_state.lock));

	if (hpet_legacy_start) {
		/* save existing mode for later reenablement */
		WARN_ON(channel != 0);
		saved_mode = pit->pit_state.channels[0].mode;
		pit->pit_state.channels[0].mode = 0xff; /* disable timer */
		pit_load_count(pit, channel, val);
		pit->pit_state.channels[0].mode = saved_mode;
	} else {
		pit_load_count(pit, channel, val);
	}
}