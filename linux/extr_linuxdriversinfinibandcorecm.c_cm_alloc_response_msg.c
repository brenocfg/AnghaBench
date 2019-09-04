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
struct ib_mad_send_buf {int dummy; } ;
struct ib_mad_recv_wc {int dummy; } ;
struct cm_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_mad_send_buf*) ; 
 int PTR_ERR (struct ib_mad_send_buf*) ; 
 struct ib_mad_send_buf* cm_alloc_response_msg_no_ah (struct cm_port*,struct ib_mad_recv_wc*) ; 
 int cm_create_response_msg_ah (struct cm_port*,struct ib_mad_recv_wc*,struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  cm_free_msg (struct ib_mad_send_buf*) ; 

__attribute__((used)) static int cm_alloc_response_msg(struct cm_port *port,
				 struct ib_mad_recv_wc *mad_recv_wc,
				 struct ib_mad_send_buf **msg)
{
	struct ib_mad_send_buf *m;
	int ret;

	m = cm_alloc_response_msg_no_ah(port, mad_recv_wc);
	if (IS_ERR(m))
		return PTR_ERR(m);

	ret = cm_create_response_msg_ah(port, mad_recv_wc, m);
	if (ret) {
		cm_free_msg(m);
		return ret;
	}

	*msg = m;
	return 0;
}