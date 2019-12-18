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
typedef  size_t uint16_t ;
struct lpfc_sglq {int dummy; } ;
struct TYPE_2__ {struct lpfc_sglq** lpfc_sglq_active_list; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */

struct lpfc_sglq *
__lpfc_clear_active_sglq(struct lpfc_hba *phba, uint16_t xritag)
{
	struct lpfc_sglq *sglq;

	sglq = phba->sli4_hba.lpfc_sglq_active_list[xritag];
	phba->sli4_hba.lpfc_sglq_active_list[xritag] = NULL;
	return sglq;
}