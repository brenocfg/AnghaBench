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
struct lpfc_sglq {int dummy; } ;
struct TYPE_3__ {int max_xri; } ;
struct TYPE_4__ {int /*<<< orphan*/  lpfc_sglq_active_list; TYPE_1__ max_cfg_param; } ;
struct lpfc_hba {TYPE_2__ sli4_hba; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_init_active_sgl_array(struct lpfc_hba *phba)
{
	int size;
	size = sizeof(struct lpfc_sglq *);
	size *= phba->sli4_hba.max_cfg_param.max_xri;

	phba->sli4_hba.lpfc_sglq_active_list =
		kzalloc(size, GFP_KERNEL);
	if (!phba->sli4_hba.lpfc_sglq_active_list)
		return -ENOMEM;
	return 0;
}