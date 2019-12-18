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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ulpStatus; } ;
struct lpfc_iocbq {TYPE_1__ iocb; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
lpfc_ct_ignore_hbq_buffer(struct lpfc_hba *phba, struct lpfc_iocbq *piocbq,
			  struct lpfc_dmabuf *mp, uint32_t size)
{
	if (!mp) {
		lpfc_printf_log(phba, KERN_INFO, LOG_ELS,
				"0146 Ignoring unsolicited CT No HBQ "
				"status = x%x\n",
				piocbq->iocb.ulpStatus);
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_ELS,
			"0145 Ignoring unsolicted CT HBQ Size:%d "
			"status = x%x\n",
			size, piocbq->iocb.ulpStatus);
}