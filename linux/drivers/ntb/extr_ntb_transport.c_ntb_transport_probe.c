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
typedef  int u64 ;
struct ntb_transport_mw {int use_msi; int mw_count; int msi_spad_offset; int msi_db_mask; unsigned int qp_count; int qp_bitmap; int qp_bitmap_free; int link_is_up; struct ntb_transport_mw* mw_vec; int /*<<< orphan*/  vbase; struct ntb_transport_mw* qp_vec; int /*<<< orphan*/  client_devs; int /*<<< orphan*/  link_cleanup; int /*<<< orphan*/  link_work; int /*<<< orphan*/  debugfs_node_dir; scalar_t__ dma_addr; int /*<<< orphan*/ * virt_addr; scalar_t__ xlat_size; scalar_t__ buff_size; int /*<<< orphan*/  phys_size; int /*<<< orphan*/  phys_addr; struct ntb_dev* ndev; } ;
struct ntb_transport_ctx {int use_msi; int mw_count; int msi_spad_offset; int msi_db_mask; unsigned int qp_count; int qp_bitmap; int qp_bitmap_free; int link_is_up; struct ntb_transport_ctx* mw_vec; int /*<<< orphan*/  vbase; struct ntb_transport_ctx* qp_vec; int /*<<< orphan*/  client_devs; int /*<<< orphan*/  link_cleanup; int /*<<< orphan*/  link_work; int /*<<< orphan*/  debugfs_node_dir; scalar_t__ dma_addr; int /*<<< orphan*/ * virt_addr; scalar_t__ xlat_size; scalar_t__ buff_size; int /*<<< orphan*/  phys_size; int /*<<< orphan*/  phys_addr; struct ntb_dev* ndev; } ;
struct ntb_dev {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct ntb_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mw_set_trans; } ;

/* Variables and functions */
 int BIT_ULL (unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MW0_SZ_HIGH ; 
 scalar_t__ NTB_DEF_PEER_CNT ; 
 int /*<<< orphan*/  NTB_SPEED_AUTO ; 
 unsigned int NTB_TRANSPORT_MIN_SPADS ; 
 int /*<<< orphan*/  NTB_WIDTH_AUTO ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned int ilog2 (int) ; 
 int /*<<< orphan*/  ioremap_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 void* kcalloc_node (unsigned int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct ntb_transport_mw*) ; 
 struct ntb_transport_mw* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 unsigned int max_num_clients ; 
 int min (unsigned int,unsigned int) ; 
 scalar_t__ nt_debugfs_dir ; 
 int ntb_bus_init (struct ntb_transport_mw*) ; 
 int /*<<< orphan*/  ntb_clear_ctx (struct ntb_dev*) ; 
 int /*<<< orphan*/  ntb_db_clear_mask (struct ntb_dev*,int) ; 
 scalar_t__ ntb_db_is_unsafe (struct ntb_dev*) ; 
 int ntb_db_valid_mask (struct ntb_dev*) ; 
 int /*<<< orphan*/  ntb_link_enable (struct ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_event (struct ntb_dev*) ; 
 int ntb_msi_init (struct ntb_dev*,int /*<<< orphan*/ ) ; 
 unsigned int ntb_peer_mw_count (struct ntb_dev*) ; 
 int ntb_peer_mw_get_addr (struct ntb_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ntb_peer_port_count (struct ntb_dev*) ; 
 int ntb_set_ctx (struct ntb_dev*,struct ntb_transport_mw*,int /*<<< orphan*/ *) ; 
 unsigned int ntb_spad_count (struct ntb_dev*) ; 
 scalar_t__ ntb_spad_is_unsafe (struct ntb_dev*) ; 
 int ntb_transport_init_queue (struct ntb_transport_mw*,int) ; 
 int /*<<< orphan*/  ntb_transport_link_cleanup_work ; 
 int /*<<< orphan*/  ntb_transport_link_work ; 
 int /*<<< orphan*/  ntb_transport_msi_desc_changed ; 
 int /*<<< orphan*/  ntb_transport_ops ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 scalar_t__ use_msi ; 

__attribute__((used)) static int ntb_transport_probe(struct ntb_client *self, struct ntb_dev *ndev)
{
	struct ntb_transport_ctx *nt;
	struct ntb_transport_mw *mw;
	unsigned int mw_count, qp_count, spad_count, max_mw_count_for_spads;
	u64 qp_bitmap;
	int node;
	int rc, i;

	mw_count = ntb_peer_mw_count(ndev);

	if (!ndev->ops->mw_set_trans) {
		dev_err(&ndev->dev, "Inbound MW based NTB API is required\n");
		return -EINVAL;
	}

	if (ntb_db_is_unsafe(ndev))
		dev_dbg(&ndev->dev,
			"doorbell is unsafe, proceed anyway...\n");
	if (ntb_spad_is_unsafe(ndev))
		dev_dbg(&ndev->dev,
			"scratchpad is unsafe, proceed anyway...\n");

	if (ntb_peer_port_count(ndev) != NTB_DEF_PEER_CNT)
		dev_warn(&ndev->dev, "Multi-port NTB devices unsupported\n");

	node = dev_to_node(&ndev->dev);

	nt = kzalloc_node(sizeof(*nt), GFP_KERNEL, node);
	if (!nt)
		return -ENOMEM;

	nt->ndev = ndev;

	/*
	 * If we are using MSI, and have at least one extra memory window,
	 * we will reserve the last MW for the MSI window.
	 */
	if (use_msi && mw_count > 1) {
		rc = ntb_msi_init(ndev, ntb_transport_msi_desc_changed);
		if (!rc) {
			mw_count -= 1;
			nt->use_msi = true;
		}
	}

	spad_count = ntb_spad_count(ndev);

	/* Limit the MW's based on the availability of scratchpads */

	if (spad_count < NTB_TRANSPORT_MIN_SPADS) {
		nt->mw_count = 0;
		rc = -EINVAL;
		goto err;
	}

	max_mw_count_for_spads = (spad_count - MW0_SZ_HIGH) / 2;
	nt->mw_count = min(mw_count, max_mw_count_for_spads);

	nt->msi_spad_offset = nt->mw_count * 2 + MW0_SZ_HIGH;

	nt->mw_vec = kcalloc_node(mw_count, sizeof(*nt->mw_vec),
				  GFP_KERNEL, node);
	if (!nt->mw_vec) {
		rc = -ENOMEM;
		goto err;
	}

	for (i = 0; i < mw_count; i++) {
		mw = &nt->mw_vec[i];

		rc = ntb_peer_mw_get_addr(ndev, i, &mw->phys_addr,
					  &mw->phys_size);
		if (rc)
			goto err1;

		mw->vbase = ioremap_wc(mw->phys_addr, mw->phys_size);
		if (!mw->vbase) {
			rc = -ENOMEM;
			goto err1;
		}

		mw->buff_size = 0;
		mw->xlat_size = 0;
		mw->virt_addr = NULL;
		mw->dma_addr = 0;
	}

	qp_bitmap = ntb_db_valid_mask(ndev);

	qp_count = ilog2(qp_bitmap);
	if (nt->use_msi) {
		qp_count -= 1;
		nt->msi_db_mask = 1 << qp_count;
		ntb_db_clear_mask(ndev, nt->msi_db_mask);
	}

	if (max_num_clients && max_num_clients < qp_count)
		qp_count = max_num_clients;
	else if (nt->mw_count < qp_count)
		qp_count = nt->mw_count;

	qp_bitmap &= BIT_ULL(qp_count) - 1;

	nt->qp_count = qp_count;
	nt->qp_bitmap = qp_bitmap;
	nt->qp_bitmap_free = qp_bitmap;

	nt->qp_vec = kcalloc_node(qp_count, sizeof(*nt->qp_vec),
				  GFP_KERNEL, node);
	if (!nt->qp_vec) {
		rc = -ENOMEM;
		goto err1;
	}

	if (nt_debugfs_dir) {
		nt->debugfs_node_dir =
			debugfs_create_dir(pci_name(ndev->pdev),
					   nt_debugfs_dir);
	}

	for (i = 0; i < qp_count; i++) {
		rc = ntb_transport_init_queue(nt, i);
		if (rc)
			goto err2;
	}

	INIT_DELAYED_WORK(&nt->link_work, ntb_transport_link_work);
	INIT_WORK(&nt->link_cleanup, ntb_transport_link_cleanup_work);

	rc = ntb_set_ctx(ndev, nt, &ntb_transport_ops);
	if (rc)
		goto err2;

	INIT_LIST_HEAD(&nt->client_devs);
	rc = ntb_bus_init(nt);
	if (rc)
		goto err3;

	nt->link_is_up = false;
	ntb_link_enable(ndev, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	ntb_link_event(ndev);

	return 0;

err3:
	ntb_clear_ctx(ndev);
err2:
	kfree(nt->qp_vec);
err1:
	while (i--) {
		mw = &nt->mw_vec[i];
		iounmap(mw->vbase);
	}
	kfree(nt->mw_vec);
err:
	kfree(nt);
	return rc;
}