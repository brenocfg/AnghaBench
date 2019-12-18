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
typedef  scalar_t__ u64 ;
struct qla_hw_data {int curr_window; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA2XXX_DRIVER_NAME ; 
 scalar_t__ QLA82XX_CRB_DDR_NET ; 
 scalar_t__ QLA82XX_CRB_MAX ; 
 scalar_t__ QLA82XX_CRB_PCIX_HOST ; 
 scalar_t__ QLA82XX_CRB_PCIX_HOST2 ; 
 scalar_t__ QLA82XX_PCI_CAMQM_MAX ; 
 scalar_t__ QLA82XX_PCI_DIRECT_CRB ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 

__attribute__((used)) static inline unsigned long
qla82xx_pci_set_crbwindow(struct qla_hw_data *ha, u64 off)
{
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	/* See if we are currently pointing to the region we want to use next */
	if ((off >= QLA82XX_CRB_PCIX_HOST) && (off < QLA82XX_CRB_DDR_NET)) {
		/* No need to change window. PCIX and PCIEregs are in both
		 * regs are in both windows.
		 */
		return off;
	}

	if ((off >= QLA82XX_CRB_PCIX_HOST) && (off < QLA82XX_CRB_PCIX_HOST2)) {
		/* We are in first CRB window */
		if (ha->curr_window != 0)
			WARN_ON(1);
		return off;
	}

	if ((off > QLA82XX_CRB_PCIX_HOST2) && (off < QLA82XX_CRB_MAX)) {
		/* We are in second CRB window */
		off = off - QLA82XX_CRB_PCIX_HOST2 + QLA82XX_CRB_PCIX_HOST;

		if (ha->curr_window != 1)
			return off;

		/* We are in the QM or direct access
		 * register region - do nothing
		 */
		if ((off >= QLA82XX_PCI_DIRECT_CRB) &&
			(off < QLA82XX_PCI_CAMQM_MAX))
			return off;
	}
	/* strange address given */
	ql_dbg(ql_dbg_p3p, vha, 0xb001,
	    "%s: Warning: unm_nic_pci_set_crbwindow "
	    "called with an unknown address(%llx).\n",
	    QLA2XXX_DRIVER_NAME, off);
	return off;
}