#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  intermediate_buffer_phys_addr; int /*<<< orphan*/  dmae_cmd_phys_addr; int /*<<< orphan*/ * p_completion_word; int /*<<< orphan*/ * p_intermediate_buffer; struct dmae_cmd* p_dmae_cmd; int /*<<< orphan*/  completion_word_phys_addr; } ;
struct qed_hwfn {int /*<<< orphan*/  rel_pf_id; TYPE_3__ dmae_info; TYPE_2__* cdev; } ;
struct dmae_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMAE_MAX_RW_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_dmae_info_free (struct qed_hwfn*) ; 

int qed_dmae_info_alloc(struct qed_hwfn *p_hwfn)
{
	dma_addr_t *p_addr = &p_hwfn->dmae_info.completion_word_phys_addr;
	struct dmae_cmd **p_cmd = &p_hwfn->dmae_info.p_dmae_cmd;
	u32 **p_buff = &p_hwfn->dmae_info.p_intermediate_buffer;
	u32 **p_comp = &p_hwfn->dmae_info.p_completion_word;

	*p_comp = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				     sizeof(u32), p_addr, GFP_KERNEL);
	if (!*p_comp)
		goto err;

	p_addr = &p_hwfn->dmae_info.dmae_cmd_phys_addr;
	*p_cmd = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    sizeof(struct dmae_cmd),
				    p_addr, GFP_KERNEL);
	if (!*p_cmd)
		goto err;

	p_addr = &p_hwfn->dmae_info.intermediate_buffer_phys_addr;
	*p_buff = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				     sizeof(u32) * DMAE_MAX_RW_SIZE,
				     p_addr, GFP_KERNEL);
	if (!*p_buff)
		goto err;

	p_hwfn->dmae_info.channel = p_hwfn->rel_pf_id;

	return 0;
err:
	qed_dmae_info_free(p_hwfn);
	return -ENOMEM;
}