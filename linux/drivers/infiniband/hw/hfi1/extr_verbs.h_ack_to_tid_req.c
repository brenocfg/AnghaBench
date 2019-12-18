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
struct tid_rdma_request {int dummy; } ;
struct rvt_ack_entry {scalar_t__ priv; } ;
struct hfi1_ack_priv {struct tid_rdma_request tid_req; } ;

/* Variables and functions */

__attribute__((used)) static inline struct tid_rdma_request *ack_to_tid_req(struct rvt_ack_entry *e)
{
	return &((struct hfi1_ack_priv *)e->priv)->tid_req;
}