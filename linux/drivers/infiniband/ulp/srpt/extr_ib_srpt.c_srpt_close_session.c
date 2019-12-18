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
struct srpt_rdma_ch {int dummy; } ;
struct se_session {struct srpt_rdma_ch* fabric_sess_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  srpt_disconnect_ch_sync (struct srpt_rdma_ch*) ; 

__attribute__((used)) static void srpt_close_session(struct se_session *se_sess)
{
	struct srpt_rdma_ch *ch = se_sess->fabric_sess_ptr;

	srpt_disconnect_ch_sync(ch);
}