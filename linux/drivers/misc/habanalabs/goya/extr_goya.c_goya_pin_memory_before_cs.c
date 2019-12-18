#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct packet_lin_dma {int /*<<< orphan*/  tsize; } ;
struct hl_userptr {int dma_mapped; int dir; TYPE_2__* sgt; int /*<<< orphan*/  job_node; } ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct hl_cs_parser {int /*<<< orphan*/  patched_cb_size; int /*<<< orphan*/  job_userptr_list; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_3__ {int (* asic_dma_map_sg ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ goya_get_dma_desc_list_size (struct hl_device*,TYPE_2__*) ; 
 int hl_pin_host_memory (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hl_userptr*) ; 
 int /*<<< orphan*/  hl_unpin_host_memory (struct hl_device*,struct hl_userptr*) ; 
 scalar_t__ hl_userptr_is_pinned (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hl_userptr**) ; 
 int /*<<< orphan*/  kfree (struct hl_userptr*) ; 
 struct hl_userptr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int goya_pin_memory_before_cs(struct hl_device *hdev,
				struct hl_cs_parser *parser,
				struct packet_lin_dma *user_dma_pkt,
				u64 addr, enum dma_data_direction dir)
{
	struct hl_userptr *userptr;
	int rc;

	if (hl_userptr_is_pinned(hdev, addr, le32_to_cpu(user_dma_pkt->tsize),
			parser->job_userptr_list, &userptr))
		goto already_pinned;

	userptr = kzalloc(sizeof(*userptr), GFP_ATOMIC);
	if (!userptr)
		return -ENOMEM;

	rc = hl_pin_host_memory(hdev, addr, le32_to_cpu(user_dma_pkt->tsize),
				userptr);
	if (rc)
		goto free_userptr;

	list_add_tail(&userptr->job_node, parser->job_userptr_list);

	rc = hdev->asic_funcs->asic_dma_map_sg(hdev, userptr->sgt->sgl,
					userptr->sgt->nents, dir);
	if (rc) {
		dev_err(hdev->dev, "failed to map sgt with DMA region\n");
		goto unpin_memory;
	}

	userptr->dma_mapped = true;
	userptr->dir = dir;

already_pinned:
	parser->patched_cb_size +=
			goya_get_dma_desc_list_size(hdev, userptr->sgt);

	return 0;

unpin_memory:
	hl_unpin_host_memory(hdev, userptr);
free_userptr:
	kfree(userptr);
	return rc;
}