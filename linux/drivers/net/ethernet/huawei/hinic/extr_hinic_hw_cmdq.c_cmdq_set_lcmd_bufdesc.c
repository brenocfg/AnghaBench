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
struct TYPE_2__ {int /*<<< orphan*/  sge; } ;
struct hinic_cmdq_wqe_lcmd {TYPE_1__ buf_desc; } ;
struct hinic_cmdq_buf {int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_set_sge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmdq_set_lcmd_bufdesc(struct hinic_cmdq_wqe_lcmd *wqe_lcmd,
				  struct hinic_cmdq_buf *buf_in)
{
	hinic_set_sge(&wqe_lcmd->buf_desc.sge, buf_in->dma_addr, buf_in->size);
}