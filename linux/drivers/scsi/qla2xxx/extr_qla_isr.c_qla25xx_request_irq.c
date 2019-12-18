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
struct qla_qpair {int /*<<< orphan*/  id; } ;
struct qla_msix_entry {int have_irq; struct qla_qpair* handle; int /*<<< orphan*/  vector; int /*<<< orphan*/  name; } ;
struct qla_init_msix_entry {int /*<<< orphan*/  handler; } ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 struct qla_init_msix_entry* msix_entries ; 
 TYPE_1__* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_qpair*) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qla25xx_request_irq(struct qla_hw_data *ha, struct qla_qpair *qpair,
	struct qla_msix_entry *msix, int vector_type)
{
	const struct qla_init_msix_entry *intr = &msix_entries[vector_type];
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	int ret;

	scnprintf(msix->name, sizeof(msix->name),
	    "qla2xxx%lu_qpair%d", vha->host_no, qpair->id);
	ret = request_irq(msix->vector, intr->handler, 0, msix->name, qpair);
	if (ret) {
		ql_log(ql_log_fatal, vha, 0x00e6,
		    "MSI-X: Unable to register handler -- %x/%d.\n",
		    msix->vector, ret);
		return ret;
	}
	msix->have_irq = 1;
	msix->handle = qpair;
	return ret;
}