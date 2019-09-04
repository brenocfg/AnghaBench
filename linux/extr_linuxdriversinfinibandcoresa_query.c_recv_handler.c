#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_sa_query {int /*<<< orphan*/  (* callback ) (struct ib_sa_query*,int /*<<< orphan*/ ,struct ib_sa_mad*) ;} ;
struct ib_sa_mad {int dummy; } ;
struct ib_mad_send_buf {struct ib_sa_query** context; } ;
struct TYPE_7__ {TYPE_2__* mad; } ;
struct ib_mad_recv_wc {TYPE_3__ recv_buf; TYPE_4__* wc; } ;
struct ib_mad_agent {int dummy; } ;
struct TYPE_8__ {scalar_t__ status; } ;
struct TYPE_5__ {scalar_t__ status; } ;
struct TYPE_6__ {TYPE_1__ mad_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  stub1 (struct ib_sa_query*,int /*<<< orphan*/ ,struct ib_sa_mad*) ; 
 int /*<<< orphan*/  stub2 (struct ib_sa_query*,int /*<<< orphan*/ ,struct ib_sa_mad*) ; 

__attribute__((used)) static void recv_handler(struct ib_mad_agent *mad_agent,
			 struct ib_mad_send_buf *send_buf,
			 struct ib_mad_recv_wc *mad_recv_wc)
{
	struct ib_sa_query *query;

	if (!send_buf)
		return;

	query = send_buf->context[0];
	if (query->callback) {
		if (mad_recv_wc->wc->status == IB_WC_SUCCESS)
			query->callback(query,
					mad_recv_wc->recv_buf.mad->mad_hdr.status ?
					-EINVAL : 0,
					(struct ib_sa_mad *) mad_recv_wc->recv_buf.mad);
		else
			query->callback(query, -EIO, NULL);
	}

	ib_free_recv_mad(mad_recv_wc);
}