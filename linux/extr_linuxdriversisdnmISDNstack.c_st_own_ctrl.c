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
typedef  int /*<<< orphan*/  u_int ;
struct mISDNchannel {TYPE_1__* st; } ;
struct TYPE_4__ {int (* ctrl ) (TYPE_2__*,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_3__ {TYPE_2__* layer1; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
st_own_ctrl(struct mISDNchannel *ch, u_int cmd, void *arg)
{
	if (!ch->st || !ch->st->layer1)
		return -EINVAL;
	return ch->st->layer1->ctrl(ch->st->layer1, cmd, arg);
}