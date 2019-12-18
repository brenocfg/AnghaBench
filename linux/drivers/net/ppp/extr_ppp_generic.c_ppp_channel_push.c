#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct channel {int /*<<< orphan*/  upl; TYPE_1__* ppp; } ;
struct TYPE_2__ {int /*<<< orphan*/  xmit_recursion; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ppp_channel_push (struct channel*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppp_channel_push(struct channel *pch)
{
	read_lock_bh(&pch->upl);
	if (pch->ppp) {
		(*this_cpu_ptr(pch->ppp->xmit_recursion))++;
		__ppp_channel_push(pch);
		(*this_cpu_ptr(pch->ppp->xmit_recursion))--;
	} else {
		__ppp_channel_push(pch);
	}
	read_unlock_bh(&pch->upl);
}