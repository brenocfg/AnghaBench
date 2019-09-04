#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* phase; int allphases; } ;
struct kvm_split_mode {TYPE_2__ lpcr_sync; } ;
struct TYPE_4__ {int tid; } ;
struct TYPE_6__ {TYPE_1__ kvm_hstate; } ;

/* Variables and functions */
 int ALL (int) ; 
 int /*<<< orphan*/  HMT_low () ; 
 int /*<<< orphan*/  HMT_medium () ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_3__* local_paca ; 

__attribute__((used)) static void wait_for_sync(struct kvm_split_mode *sip, int phase)
{
	int thr = local_paca->kvm_hstate.tid;

	sip->lpcr_sync.phase[thr] |= phase;
	phase = ALL(phase);
	while ((sip->lpcr_sync.allphases & phase) != phase) {
		HMT_low();
		barrier();
	}
	HMT_medium();
}