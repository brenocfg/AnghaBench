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
typedef  int /*<<< orphan*/  u8 ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  qed_ll2_dealloc_buffer (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void qed_ll2b_release_rx_packet(void *cxt,
				       u8 connection_handle,
				       void *cookie,
				       dma_addr_t rx_buf_addr,
				       bool b_last_packet)
{
	struct qed_hwfn *p_hwfn = cxt;

	qed_ll2_dealloc_buffer(p_hwfn->cdev, cookie);
}