#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mfc_control_RW; } ;
struct spu_state {scalar_t__ suspend_time; TYPE_4__* lscsa; TYPE_1__ priv2; } ;
struct spu {int dummy; } ;
typedef  scalar_t__ cycles_t ;
struct TYPE_7__ {int /*<<< orphan*/ * slot; } ;
struct TYPE_6__ {scalar_t__* slot; } ;
struct TYPE_8__ {TYPE_3__ decr_status; TYPE_2__ decr; } ;

/* Variables and functions */
 int MFC_CNTL_DECREMENTER_RUNNING ; 
 int /*<<< orphan*/  SPU_DECR_STATUS_RUNNING ; 
 int /*<<< orphan*/  SPU_DECR_STATUS_WRAPPED ; 
 scalar_t__ get_cycles () ; 

__attribute__((used)) static inline void setup_decr(struct spu_state *csa, struct spu *spu)
{
	/* Restore, Step 34:
	 *     If CSA.MFC_CNTL[Ds]=1 (decrementer was
	 *     running) then adjust decrementer, set
	 *     decrementer running status in LSCSA,
	 *     and set decrementer "wrapped" status
	 *     in LSCSA.
	 */
	if (csa->priv2.mfc_control_RW & MFC_CNTL_DECREMENTER_RUNNING) {
		cycles_t resume_time = get_cycles();
		cycles_t delta_time = resume_time - csa->suspend_time;

		csa->lscsa->decr_status.slot[0] = SPU_DECR_STATUS_RUNNING;
		if (csa->lscsa->decr.slot[0] < delta_time) {
			csa->lscsa->decr_status.slot[0] |=
				 SPU_DECR_STATUS_WRAPPED;
		}

		csa->lscsa->decr.slot[0] -= delta_time;
	} else {
		csa->lscsa->decr_status.slot[0] = 0;
	}
}