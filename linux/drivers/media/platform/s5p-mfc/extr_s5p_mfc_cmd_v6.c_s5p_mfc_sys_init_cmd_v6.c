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
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;
struct s5p_mfc_dev {TYPE_3__ ctx_buf; int /*<<< orphan*/  mfc_ops; TYPE_2__* variant; } ;
struct s5p_mfc_cmd_args {int dummy; } ;
struct s5p_mfc_buf_size_v6 {int /*<<< orphan*/  dev_ctx; } ;
struct TYPE_5__ {TYPE_1__* buf_size; } ;
struct TYPE_4__ {struct s5p_mfc_buf_size_v6* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_FIMV_CONTEXT_MEM_ADDR_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_CONTEXT_MEM_SIZE_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_H2R_CMD_SYS_INIT_V6 ; 
 int /*<<< orphan*/  alloc_dev_context_buffer ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s5p_mfc_cmd_host2risc_v6 (struct s5p_mfc_dev*,int /*<<< orphan*/ ,struct s5p_mfc_cmd_args*) ; 
 int s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 

__attribute__((used)) static int s5p_mfc_sys_init_cmd_v6(struct s5p_mfc_dev *dev)
{
	struct s5p_mfc_cmd_args h2r_args;
	struct s5p_mfc_buf_size_v6 *buf_size = dev->variant->buf_size->priv;
	int ret;

	ret = s5p_mfc_hw_call(dev->mfc_ops, alloc_dev_context_buffer, dev);
	if (ret)
		return ret;

	mfc_write(dev, dev->ctx_buf.dma, S5P_FIMV_CONTEXT_MEM_ADDR_V6);
	mfc_write(dev, buf_size->dev_ctx, S5P_FIMV_CONTEXT_MEM_SIZE_V6);
	return s5p_mfc_cmd_host2risc_v6(dev, S5P_FIMV_H2R_CMD_SYS_INIT_V6,
					&h2r_args);
}