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
struct tty_ldisc_ops {scalar_t__ flags; scalar_t__ refcount; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 struct tty_ldisc_ops n_tty_ops ; 

void n_tty_inherit_ops(struct tty_ldisc_ops *ops)
{
	*ops = n_tty_ops;
	ops->owner = NULL;
	ops->refcount = ops->flags = 0;
}