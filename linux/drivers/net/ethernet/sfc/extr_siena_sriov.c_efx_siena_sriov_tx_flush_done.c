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
struct siena_vf {int /*<<< orphan*/  flush_waitq; int /*<<< orphan*/  txq_count; int /*<<< orphan*/  txq_mask; } ;
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 unsigned int EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSF_AZ_DRIVER_EV_SUBDATA ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ efx_vfdi_flush_wake (struct siena_vf*) ; 
 scalar_t__ map_vi_index (struct efx_nic*,unsigned int,struct siena_vf**,unsigned int*) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void efx_siena_sriov_tx_flush_done(struct efx_nic *efx, efx_qword_t *event)
{
	struct siena_vf *vf;
	unsigned queue, qid;

	queue = EFX_QWORD_FIELD(*event,  FSF_AZ_DRIVER_EV_SUBDATA);
	if (map_vi_index(efx, queue, &vf, &qid))
		return;
	/* Ignore flush completions triggered by an FLR */
	if (!test_bit(qid, vf->txq_mask))
		return;

	__clear_bit(qid, vf->txq_mask);
	--vf->txq_count;

	if (efx_vfdi_flush_wake(vf))
		wake_up(&vf->flush_waitq);
}