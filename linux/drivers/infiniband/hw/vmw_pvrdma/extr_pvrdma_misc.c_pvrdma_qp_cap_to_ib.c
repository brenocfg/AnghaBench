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
struct pvrdma_qp_cap {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_cap {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;

/* Variables and functions */

void pvrdma_qp_cap_to_ib(struct ib_qp_cap *dst, const struct pvrdma_qp_cap *src)
{
	dst->max_send_wr = src->max_send_wr;
	dst->max_recv_wr = src->max_recv_wr;
	dst->max_send_sge = src->max_send_sge;
	dst->max_recv_sge = src->max_recv_sge;
	dst->max_inline_data = src->max_inline_data;
}