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
typedef  int /*<<< orphan*/  u32 ;
struct lpfc_register {scalar_t__ word0; } ;
struct lpfc_queue {int /*<<< orphan*/  q_mode; int /*<<< orphan*/  queue_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  EQDregaddr; } ;
struct TYPE_5__ {TYPE_1__ if_type2; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct lpfc_hba {TYPE_3__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sliport_eqdelay_delay ; 
 int /*<<< orphan*/  lpfc_sliport_eqdelay_id ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lpfc_sli4_mod_hba_eq_delay(struct lpfc_hba *phba, struct lpfc_queue *eq,
			   u32 delay)
{
	struct lpfc_register reg_data;

	reg_data.word0 = 0;
	bf_set(lpfc_sliport_eqdelay_id, &reg_data, eq->queue_id);
	bf_set(lpfc_sliport_eqdelay_delay, &reg_data, delay);
	writel(reg_data.word0, phba->sli4_hba.u.if_type2.EQDregaddr);
	eq->q_mode = delay;
}