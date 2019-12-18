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
struct vmw_kms_sou_bo_blit {int dummy; } ;
struct vmw_kms_dirty {int num_hits; int /*<<< orphan*/  dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_fifo_commit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vmw_sou_bo_fifo_commit(struct vmw_kms_dirty *dirty)
{
	if (!dirty->num_hits) {
		vmw_fifo_commit(dirty->dev_priv, 0);
		return;
	}

	vmw_fifo_commit(dirty->dev_priv,
			sizeof(struct vmw_kms_sou_bo_blit) *
			dirty->num_hits);
}