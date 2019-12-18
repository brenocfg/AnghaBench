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
struct TYPE_6__ {int /*<<< orphan*/  virt; int /*<<< orphan*/  size; } ;
struct s5p_mfc_dev {TYPE_3__ ctx_buf; TYPE_2__* variant; } ;
struct s5p_mfc_buf_size_v6 {int /*<<< orphan*/  dev_ctx; } ;
struct TYPE_5__ {TYPE_1__* buf_size; } ;
struct TYPE_4__ {struct s5p_mfc_buf_size_v6* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_L_CTX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int s5p_mfc_alloc_priv_buf (struct s5p_mfc_dev*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int s5p_mfc_alloc_dev_context_buffer_v6(struct s5p_mfc_dev *dev)
{
	struct s5p_mfc_buf_size_v6 *buf_size = dev->variant->buf_size->priv;
	int ret;

	mfc_debug_enter();

	dev->ctx_buf.size = buf_size->dev_ctx;
	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &dev->ctx_buf);
	if (ret) {
		mfc_err("Failed to allocate device context buffer\n");
		return ret;
	}

	memset(dev->ctx_buf.virt, 0, buf_size->dev_ctx);
	wmb();

	mfc_debug_leave();

	return 0;
}