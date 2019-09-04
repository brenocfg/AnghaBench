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
struct qed_iwarp_ll2_buff {int /*<<< orphan*/  data_phys_addr; int /*<<< orphan*/  data; int /*<<< orphan*/  buff_size; } ;
struct qed_hwfn {TYPE_2__* cdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_iwarp_ll2_buff*) ; 

__attribute__((used)) static void qed_iwarp_ll2_rel_rx_pkt(void *cxt, u8 connection_handle,
				     void *cookie, dma_addr_t rx_buf_addr,
				     bool b_last_packet)
{
	struct qed_iwarp_ll2_buff *buffer = cookie;
	struct qed_hwfn *p_hwfn = cxt;

	dma_free_coherent(&p_hwfn->cdev->pdev->dev, buffer->buff_size,
			  buffer->data, buffer->data_phys_addr);
	kfree(buffer);
}