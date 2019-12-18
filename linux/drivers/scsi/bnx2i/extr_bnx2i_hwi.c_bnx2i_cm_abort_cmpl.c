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
struct cnic_sock {scalar_t__ context; } ;
struct bnx2i_endpoint {int /*<<< orphan*/  ofld_wait; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_STATE_DISCONN_COMPL ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2i_cm_abort_cmpl(struct cnic_sock *cm_sk)
{
	struct bnx2i_endpoint *ep = (struct bnx2i_endpoint *) cm_sk->context;

	ep->state = EP_STATE_DISCONN_COMPL;
	wake_up_interruptible(&ep->ofld_wait);
}