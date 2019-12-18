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
struct cxgbit_sock {int /*<<< orphan*/ * wr_pending_head; int /*<<< orphan*/ * wr_pending_tail; } ;

/* Variables and functions */

__attribute__((used)) static inline void cxgbit_sock_reset_wr_list(struct cxgbit_sock *csk)
{
	csk->wr_pending_tail = NULL;
	csk->wr_pending_head = NULL;
}