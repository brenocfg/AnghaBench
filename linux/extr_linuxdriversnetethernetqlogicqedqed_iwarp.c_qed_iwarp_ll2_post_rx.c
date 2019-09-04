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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_iwarp_ll2_buff {int /*<<< orphan*/  data_phys_addr; int /*<<< orphan*/  data; scalar_t__ buff_size; } ;
struct qed_hwfn {TYPE_2__* cdev; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_iwarp_ll2_buff*) ; 
 int qed_ll2_post_rx_buffer (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_iwarp_ll2_buff*,int) ; 

__attribute__((used)) static int
qed_iwarp_ll2_post_rx(struct qed_hwfn *p_hwfn,
		      struct qed_iwarp_ll2_buff *buf, u8 handle)
{
	int rc;

	rc = qed_ll2_post_rx_buffer(p_hwfn, handle, buf->data_phys_addr,
				    (u16)buf->buff_size, buf, 1);
	if (rc) {
		DP_NOTICE(p_hwfn,
			  "Failed to repost rx buffer to ll2 rc = %d, handle=%d\n",
			  rc, handle);
		dma_free_coherent(&p_hwfn->cdev->pdev->dev, buf->buff_size,
				  buf->data, buf->data_phys_addr);
		kfree(buf);
	}

	return rc;
}