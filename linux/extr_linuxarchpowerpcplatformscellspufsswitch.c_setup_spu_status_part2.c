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
typedef  int u32 ;
struct TYPE_4__ {int spu_status_R; } ;
struct spu_state {TYPE_3__* lscsa; TYPE_1__ prob; } ;
struct spu {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * slot; } ;
struct TYPE_6__ {TYPE_2__ stopped_status; } ;

/* Variables and functions */
 int SPU_STATUS_INVALID_INSTR ; 
 int SPU_STATUS_RUNNING ; 
 int SPU_STATUS_SINGLE_STEP ; 
 int SPU_STATUS_STOPPED_BY_HALT ; 
 int SPU_STATUS_STOPPED_BY_STOP ; 
 int /*<<< orphan*/  SPU_STOPPED_STATUS_R ; 

__attribute__((used)) static inline void setup_spu_status_part2(struct spu_state *csa,
					  struct spu *spu)
{
	u32 mask;

	/* Restore, Step 28:
	 *     If the CSA.SPU_Status[I,S,H,P,R]=0 then
	 *     add a 'br *' instruction to the end of
	 *     the SPU based restore code.
	 *
	 *     NOTE: Rather than modifying the SPU executable, we
	 *     instead add a new 'stopped_status' field to the
	 *     LSCSA.  The SPU-side restore reads this field and
	 *     takes the appropriate action when exiting.
	 */
	mask = SPU_STATUS_INVALID_INSTR |
	    SPU_STATUS_SINGLE_STEP |
	    SPU_STATUS_STOPPED_BY_HALT |
	    SPU_STATUS_STOPPED_BY_STOP | SPU_STATUS_RUNNING;
	if (!(csa->prob.spu_status_R & mask)) {
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_R;
	}
}