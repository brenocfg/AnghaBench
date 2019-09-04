#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_9__ {TYPE_3__ ioceth; } ;
struct bnad {int /*<<< orphan*/  bna_lock; TYPE_4__ bna; } ;
struct TYPE_6__ {int /*<<< orphan*/  iocpf_timer; } ;
struct TYPE_7__ {TYPE_1__ ioc; } ;
struct TYPE_10__ {TYPE_2__ ioceth; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_nw_iocpf_timeout (int /*<<< orphan*/ *) ; 
 TYPE_5__ bna ; 
 struct bnad* bnad ; 
 struct bnad* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bnad_iocpf_timeout(struct timer_list *t)
{
	struct bnad *bnad = from_timer(bnad, t, bna.ioceth.ioc.iocpf_timer);
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_iocpf_timeout(&bnad->bna.ioceth.ioc);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}