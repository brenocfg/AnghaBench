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
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * p_intermediate_buffer; int /*<<< orphan*/  intermediate_buffer_phys_addr; int /*<<< orphan*/ * p_dmae_cmd; int /*<<< orphan*/  dmae_cmd_phys_addr; int /*<<< orphan*/ * p_completion_word; int /*<<< orphan*/  completion_word_phys_addr; } ;
struct qed_hwfn {TYPE_3__ dmae_info; TYPE_2__* cdev; } ;
struct dmae_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMAE_MAX_RW_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void qed_dmae_info_free(struct qed_hwfn *p_hwfn)
{
	dma_addr_t p_phys;

	/* Just make sure no one is in the middle */
	mutex_lock(&p_hwfn->dmae_info.mutex);

	if (p_hwfn->dmae_info.p_completion_word) {
		p_phys = p_hwfn->dmae_info.completion_word_phys_addr;
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  sizeof(u32),
				  p_hwfn->dmae_info.p_completion_word, p_phys);
		p_hwfn->dmae_info.p_completion_word = NULL;
	}

	if (p_hwfn->dmae_info.p_dmae_cmd) {
		p_phys = p_hwfn->dmae_info.dmae_cmd_phys_addr;
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  sizeof(struct dmae_cmd),
				  p_hwfn->dmae_info.p_dmae_cmd, p_phys);
		p_hwfn->dmae_info.p_dmae_cmd = NULL;
	}

	if (p_hwfn->dmae_info.p_intermediate_buffer) {
		p_phys = p_hwfn->dmae_info.intermediate_buffer_phys_addr;
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  sizeof(u32) * DMAE_MAX_RW_SIZE,
				  p_hwfn->dmae_info.p_intermediate_buffer,
				  p_phys);
		p_hwfn->dmae_info.p_intermediate_buffer = NULL;
	}

	mutex_unlock(&p_hwfn->dmae_info.mutex);
}