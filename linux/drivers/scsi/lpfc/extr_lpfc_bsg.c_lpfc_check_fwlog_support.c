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
struct lpfc_ras_fwlog {int ras_hwsupport; int ras_enabled; } ;
struct lpfc_hba {struct lpfc_ras_fwlog ras_fwlog; } ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 

int
lpfc_check_fwlog_support(struct lpfc_hba *phba)
{
	struct lpfc_ras_fwlog *ras_fwlog = NULL;

	ras_fwlog = &phba->ras_fwlog;

	if (ras_fwlog->ras_hwsupport == false)
		return -EACCES;
	else if (ras_fwlog->ras_enabled == false)
		return -EPERM;
	else
		return 0;
}