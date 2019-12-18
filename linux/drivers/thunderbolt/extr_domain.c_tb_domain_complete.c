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
struct tb {TYPE_1__* cm_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (struct tb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tb*) ; 

void tb_domain_complete(struct tb *tb)
{
	if (tb->cm_ops->complete)
		tb->cm_ops->complete(tb);
}