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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct msix_entry {int dummy; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_aeqs {int num_aeqs; int /*<<< orphan*/  workq; int /*<<< orphan*/ * aeq; struct hinic_hwif* hwif; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HINIC_AEQ ; 
 int /*<<< orphan*/  HINIC_EQS_WQ_NAME ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int init_eq (int /*<<< orphan*/ *,struct hinic_hwif*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msix_entry) ; 
 int /*<<< orphan*/  remove_eq (int /*<<< orphan*/ *) ; 

int hinic_aeqs_init(struct hinic_aeqs *aeqs, struct hinic_hwif *hwif,
		    int num_aeqs, u32 q_len, u32 page_size,
		    struct msix_entry *msix_entries)
{
	struct pci_dev *pdev = hwif->pdev;
	int err, i, q_id;

	aeqs->workq = create_singlethread_workqueue(HINIC_EQS_WQ_NAME);
	if (!aeqs->workq)
		return -ENOMEM;

	aeqs->hwif = hwif;
	aeqs->num_aeqs = num_aeqs;

	for (q_id = 0; q_id < num_aeqs; q_id++) {
		err = init_eq(&aeqs->aeq[q_id], hwif, HINIC_AEQ, q_id, q_len,
			      page_size, msix_entries[q_id]);
		if (err) {
			dev_err(&pdev->dev, "Failed to init aeq %d\n", q_id);
			goto err_init_aeq;
		}
	}

	return 0;

err_init_aeq:
	for (i = 0; i < q_id; i++)
		remove_eq(&aeqs->aeq[i]);

	destroy_workqueue(aeqs->workq);
	return err;
}