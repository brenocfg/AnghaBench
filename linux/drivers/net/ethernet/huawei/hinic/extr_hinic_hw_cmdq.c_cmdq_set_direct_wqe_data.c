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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  buf_len; } ;
struct hinic_cmdq_wqe_scmd {TYPE_1__ buf_desc; } ;
struct hinic_cmdq_direct_wqe {struct hinic_cmdq_wqe_scmd wqe_scmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmdq_set_direct_wqe_data(struct hinic_cmdq_direct_wqe *wqe,
				     void *buf_in, u32 in_size)
{
	struct hinic_cmdq_wqe_scmd *wqe_scmd = &wqe->wqe_scmd;

	wqe_scmd->buf_desc.buf_len = in_size;
	memcpy(wqe_scmd->buf_desc.data, buf_in, in_size);
}