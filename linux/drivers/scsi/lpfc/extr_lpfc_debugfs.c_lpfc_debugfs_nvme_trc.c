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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct lpfc_hba {int nvmeio_trc_size; struct lpfc_debugfs_nvmeio_trc* nvmeio_trc; int /*<<< orphan*/  nvmeio_trc_cnt; int /*<<< orphan*/  nvmeio_trc_on; } ;
struct lpfc_debugfs_nvmeio_trc {char* fmt; int /*<<< orphan*/  data3; void* data2; void* data1; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

inline void
lpfc_debugfs_nvme_trc(struct lpfc_hba *phba, char *fmt,
		      uint16_t data1, uint16_t data2, uint32_t data3)
{
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	struct lpfc_debugfs_nvmeio_trc *dtp;
	int index;

	if (!phba->nvmeio_trc_on || !phba->nvmeio_trc)
		return;

	index = atomic_inc_return(&phba->nvmeio_trc_cnt) &
		(phba->nvmeio_trc_size - 1);
	dtp = phba->nvmeio_trc + index;
	dtp->fmt = fmt;
	dtp->data1 = data1;
	dtp->data2 = data2;
	dtp->data3 = data3;
#endif
}