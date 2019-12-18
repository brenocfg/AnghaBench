#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct adv_dvc_var {TYPE_1__* carr_freelist; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_vpa; } ;
typedef  TYPE_1__ ADV_CARR_T ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_CQ_STOPPER ; 
 int /*<<< orphan*/  ASC_DBG (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* adv_get_carrier (struct adv_dvc_var*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ADV_CARR_T *adv_get_next_carrier(struct adv_dvc_var *adv_dvc)
{
	ADV_CARR_T *carrp = adv_dvc->carr_freelist;
	u32 next_vpa = le32_to_cpu(carrp->next_vpa);

	if (next_vpa == 0 || next_vpa == ~0) {
		ASC_DBG(1, "invalid vpa offset 0x%x\n", next_vpa);
		return NULL;
	}

	adv_dvc->carr_freelist = adv_get_carrier(adv_dvc, next_vpa);
	/*
	 * insert stopper carrier to terminate list
	 */
	carrp->next_vpa = cpu_to_le32(ADV_CQ_STOPPER);

	return carrp;
}