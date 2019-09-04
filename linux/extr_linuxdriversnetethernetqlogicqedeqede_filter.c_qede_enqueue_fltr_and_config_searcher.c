#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct qede_dev {TYPE_3__* arfs; int /*<<< orphan*/  cdev; TYPE_2__* ops; TYPE_1__* pdev; } ;
struct TYPE_8__ {scalar_t__ mode; } ;
struct qede_arfs_fltr_node {TYPE_4__ tuple; int /*<<< orphan*/  node; int /*<<< orphan*/  mapping; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int filter_count; scalar_t__ mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* configure_arfs_searcher ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QEDE_ARFS_BUCKET_HEAD (struct qede_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ QED_FILTER_CONFIG_MODE_DISABLE ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_free_arfs_filter (struct qede_dev*,struct qede_arfs_fltr_node*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
qede_enqueue_fltr_and_config_searcher(struct qede_dev *edev,
				      struct qede_arfs_fltr_node *fltr,
				      u16 bucket_idx)
{
	fltr->mapping = dma_map_single(&edev->pdev->dev, fltr->data,
				       fltr->buf_len, DMA_TO_DEVICE);
	if (dma_mapping_error(&edev->pdev->dev, fltr->mapping)) {
		DP_NOTICE(edev, "Failed to map DMA memory for rule\n");
		qede_free_arfs_filter(edev, fltr);
		return -ENOMEM;
	}

	INIT_HLIST_NODE(&fltr->node);
	hlist_add_head(&fltr->node,
		       QEDE_ARFS_BUCKET_HEAD(edev, bucket_idx));

	edev->arfs->filter_count++;
	if (edev->arfs->filter_count == 1 &&
	    edev->arfs->mode == QED_FILTER_CONFIG_MODE_DISABLE) {
		edev->ops->configure_arfs_searcher(edev->cdev,
						   fltr->tuple.mode);
		edev->arfs->mode = fltr->tuple.mode;
	}

	return 0;
}