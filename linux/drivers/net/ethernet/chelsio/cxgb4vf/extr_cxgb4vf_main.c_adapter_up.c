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
struct adapter {int flags; int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  name; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CXGB4VF_FULL_INIT_DONE ; 
 int CXGB4VF_USING_MSI ; 
 int CXGB4VF_USING_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  enable_rx (struct adapter*) ; 
 int /*<<< orphan*/  name_msix_vecs (struct adapter*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adapter*) ; 
 int request_msix_queue_irqs (struct adapter*) ; 
 int setup_rss (struct adapter*) ; 
 int setup_sge_queues (struct adapter*) ; 
 int /*<<< orphan*/  t4vf_free_sge_resources (struct adapter*) ; 
 int /*<<< orphan*/  t4vf_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  t4vf_sge_start (struct adapter*) ; 

__attribute__((used)) static int adapter_up(struct adapter *adapter)
{
	int err;

	/*
	 * If this is the first time we've been called, perform basic
	 * adapter setup.  Once we've done this, many of our adapter
	 * parameters can no longer be changed ...
	 */
	if ((adapter->flags & CXGB4VF_FULL_INIT_DONE) == 0) {
		err = setup_sge_queues(adapter);
		if (err)
			return err;
		err = setup_rss(adapter);
		if (err) {
			t4vf_free_sge_resources(adapter);
			return err;
		}

		if (adapter->flags & CXGB4VF_USING_MSIX)
			name_msix_vecs(adapter);

		adapter->flags |= CXGB4VF_FULL_INIT_DONE;
	}

	/*
	 * Acquire our interrupt resources.  We only support MSI-X and MSI.
	 */
	BUG_ON((adapter->flags &
	       (CXGB4VF_USING_MSIX | CXGB4VF_USING_MSI)) == 0);
	if (adapter->flags & CXGB4VF_USING_MSIX)
		err = request_msix_queue_irqs(adapter);
	else
		err = request_irq(adapter->pdev->irq,
				  t4vf_intr_handler(adapter), 0,
				  adapter->name, adapter);
	if (err) {
		dev_err(adapter->pdev_dev, "request_irq failed, err %d\n",
			err);
		return err;
	}

	/*
	 * Enable NAPI ingress processing and return success.
	 */
	enable_rx(adapter);
	t4vf_sge_start(adapter);

	return 0;
}