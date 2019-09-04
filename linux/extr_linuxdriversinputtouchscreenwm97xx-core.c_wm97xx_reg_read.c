#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct wm97xx {TYPE_3__* ac97; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* read ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

int wm97xx_reg_read(struct wm97xx *wm, u16 reg)
{
	if (wm->ac97)
		return wm->ac97->bus->ops->read(wm->ac97, reg);
	else
		return -1;
}