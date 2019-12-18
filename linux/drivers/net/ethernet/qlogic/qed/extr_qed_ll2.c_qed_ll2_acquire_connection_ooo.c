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
typedef  int u16 ;
struct qed_ooo_buffer {int rx_buffer_size; void* rx_buffer_virt_addr; int /*<<< orphan*/  rx_buffer_phys_addr; } ;
struct TYPE_6__ {scalar_t__ conn_type; int rx_num_ooo_buffers; int rx_num_desc; } ;
struct qed_ll2_info {TYPE_3__ input; } ;
struct qed_hwfn {int /*<<< orphan*/  p_ooo_info; TYPE_2__* cdev; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ QED_LL2_TYPE_OOO ; 
 int /*<<< orphan*/  QED_MSG_LL2 ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_ooo_buffer*) ; 
 struct qed_ooo_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ooo_put_free_buffer (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_ooo_buffer*) ; 

__attribute__((used)) static int
qed_ll2_acquire_connection_ooo(struct qed_hwfn *p_hwfn,
			       struct qed_ll2_info *p_ll2_info, u16 mtu)
{
	struct qed_ooo_buffer *p_buf = NULL;
	void *p_virt;
	u16 buf_idx;
	int rc = 0;

	if (p_ll2_info->input.conn_type != QED_LL2_TYPE_OOO)
		return rc;

	/* Correct number of requested OOO buffers if needed */
	if (!p_ll2_info->input.rx_num_ooo_buffers) {
		u16 num_desc = p_ll2_info->input.rx_num_desc;

		if (!num_desc)
			return -EINVAL;
		p_ll2_info->input.rx_num_ooo_buffers = num_desc * 2;
	}

	for (buf_idx = 0; buf_idx < p_ll2_info->input.rx_num_ooo_buffers;
	     buf_idx++) {
		p_buf = kzalloc(sizeof(*p_buf), GFP_KERNEL);
		if (!p_buf) {
			rc = -ENOMEM;
			goto out;
		}

		p_buf->rx_buffer_size = mtu + 26 + ETH_CACHE_LINE_SIZE;
		p_buf->rx_buffer_size = (p_buf->rx_buffer_size +
					 ETH_CACHE_LINE_SIZE - 1) &
					~(ETH_CACHE_LINE_SIZE - 1);
		p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					    p_buf->rx_buffer_size,
					    &p_buf->rx_buffer_phys_addr,
					    GFP_KERNEL);
		if (!p_virt) {
			kfree(p_buf);
			rc = -ENOMEM;
			goto out;
		}

		p_buf->rx_buffer_virt_addr = p_virt;
		qed_ooo_put_free_buffer(p_hwfn, p_hwfn->p_ooo_info, p_buf);
	}

	DP_VERBOSE(p_hwfn, QED_MSG_LL2,
		   "Allocated [%04x] LL2 OOO buffers [each of size 0x%08x]\n",
		   p_ll2_info->input.rx_num_ooo_buffers, p_buf->rx_buffer_size);

out:
	return rc;
}