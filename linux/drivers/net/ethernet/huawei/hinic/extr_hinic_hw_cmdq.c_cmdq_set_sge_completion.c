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
struct hinic_sge_resp {int /*<<< orphan*/  sge; } ;
struct hinic_cmdq_completion {struct hinic_sge_resp sge_resp; } ;
struct hinic_cmdq_buf {int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_set_sge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmdq_set_sge_completion(struct hinic_cmdq_completion *completion,
				    struct hinic_cmdq_buf *buf_out)
{
	struct hinic_sge_resp *sge_resp = &completion->sge_resp;

	hinic_set_sge(&sge_resp->sge, buf_out->dma_addr, buf_out->size);
}