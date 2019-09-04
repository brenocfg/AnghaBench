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
struct qed_sb_attn_info {int /*<<< orphan*/  sb_phys; scalar_t__ sb_attn; } ;
struct qed_hwfn {struct qed_sb_attn_info* p_sb_attn; TYPE_2__* cdev; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_ATTN_ALIGNED_SIZE (struct qed_hwfn*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_sb_attn_info*) ; 

__attribute__((used)) static void qed_int_sb_attn_free(struct qed_hwfn *p_hwfn)
{
	struct qed_sb_attn_info *p_sb = p_hwfn->p_sb_attn;

	if (!p_sb)
		return;

	if (p_sb->sb_attn)
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  SB_ATTN_ALIGNED_SIZE(p_hwfn),
				  p_sb->sb_attn, p_sb->sb_phys);
	kfree(p_sb);
	p_hwfn->p_sb_attn = NULL;
}