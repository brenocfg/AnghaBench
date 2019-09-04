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
struct ib_qp {int dummy; } ;
struct ib_mad_agent {int dummy; } ;
typedef  int /*<<< orphan*/  ib_mad_send_handler ;
typedef  int /*<<< orphan*/  ib_mad_recv_handler ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_mad_agent* ERR_PTR (int /*<<< orphan*/ ) ; 

struct ib_mad_agent *ib_redirect_mad_qp(struct ib_qp *qp,
					u8 rmpp_version,
					ib_mad_send_handler send_handler,
					ib_mad_recv_handler recv_handler,
					void *context)
{
	return ERR_PTR(-EINVAL);	/* XXX: for now */
}