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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct memstick_host {int dummy; } ;
struct jmb38x_ms {int host_cnt; int /*<<< orphan*/ ** hosts; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jmb38x_ms_alloc_host (struct jmb38x_ms*,int) ; 
 int jmb38x_ms_count_slots (struct pci_dev*) ; 
 int /*<<< orphan*/  jmb38x_ms_free_host (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jmb38x_ms_pmos (struct pci_dev*,int) ; 
 int /*<<< orphan*/  kfree (struct jmb38x_ms*) ; 
 struct jmb38x_ms* kzalloc (int,int /*<<< orphan*/ ) ; 
 int memstick_add_host (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct jmb38x_ms*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int jmb38x_ms_probe(struct pci_dev *pdev,
			   const struct pci_device_id *dev_id)
{
	struct jmb38x_ms *jm;
	int pci_dev_busy = 0;
	int rc, cnt;

	rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (rc)
		return rc;

	rc = pci_enable_device(pdev);
	if (rc)
		return rc;

	pci_set_master(pdev);

	rc = pci_request_regions(pdev, DRIVER_NAME);
	if (rc) {
		pci_dev_busy = 1;
		goto err_out;
	}

	jmb38x_ms_pmos(pdev, 1);

	cnt = jmb38x_ms_count_slots(pdev);
	if (!cnt) {
		rc = -ENODEV;
		pci_dev_busy = 1;
		goto err_out_int;
	}

	jm = kzalloc(sizeof(struct jmb38x_ms)
		     + cnt * sizeof(struct memstick_host *), GFP_KERNEL);
	if (!jm) {
		rc = -ENOMEM;
		goto err_out_int;
	}

	jm->pdev = pdev;
	jm->host_cnt = cnt;
	pci_set_drvdata(pdev, jm);

	for (cnt = 0; cnt < jm->host_cnt; ++cnt) {
		jm->hosts[cnt] = jmb38x_ms_alloc_host(jm, cnt);
		if (!jm->hosts[cnt])
			break;

		rc = memstick_add_host(jm->hosts[cnt]);

		if (rc) {
			jmb38x_ms_free_host(jm->hosts[cnt]);
			jm->hosts[cnt] = NULL;
			break;
		}
	}

	if (cnt)
		return 0;

	rc = -ENODEV;

	pci_set_drvdata(pdev, NULL);
	kfree(jm);
err_out_int:
	pci_release_regions(pdev);
err_out:
	if (!pci_dev_busy)
		pci_disable_device(pdev);
	return rc;
}