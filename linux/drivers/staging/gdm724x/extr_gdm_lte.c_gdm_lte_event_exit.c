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
struct TYPE_4__ {scalar_t__ ref_cnt; TYPE_1__* sock; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_socket; } ;

/* Variables and functions */
 TYPE_2__ lte_event ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ ) ; 

void gdm_lte_event_exit(void)
{
	if (lte_event.sock && --lte_event.ref_cnt == 0) {
		sock_release(lte_event.sock->sk_socket);
		lte_event.sock = NULL;
	}
}