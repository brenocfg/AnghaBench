#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct kvm_kpit_channel_state* channels; scalar_t__ flags; } ;
struct kvm_pit {TYPE_1__ pit_state; } ;
struct kvm_kpit_channel_state {int mode; int gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_pit_reset_reinject (struct kvm_pit*) ; 
 int /*<<< orphan*/  pit_load_count (struct kvm_pit*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_pit_reset(struct kvm_pit *pit)
{
	int i;
	struct kvm_kpit_channel_state *c;

	pit->pit_state.flags = 0;
	for (i = 0; i < 3; i++) {
		c = &pit->pit_state.channels[i];
		c->mode = 0xff;
		c->gate = (i != 2);
		pit_load_count(pit, i, 0);
	}

	kvm_pit_reset_reinject(pit);
}