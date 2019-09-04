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
struct TYPE_2__ {int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  pending; } ;
struct kvm_pit {TYPE_1__ pit_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void kvm_pit_reset_reinject(struct kvm_pit *pit)
{
	atomic_set(&pit->pit_state.pending, 0);
	atomic_set(&pit->pit_state.irq_ack, 1);
}