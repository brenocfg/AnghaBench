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
struct throtl_grp {int flags; } ;

/* Variables and functions */
 int THROTL_TG_PENDING ; 
 int /*<<< orphan*/  __throtl_dequeue_tg (struct throtl_grp*) ; 

__attribute__((used)) static void throtl_dequeue_tg(struct throtl_grp *tg)
{
	if (tg->flags & THROTL_TG_PENDING)
		__throtl_dequeue_tg(tg);
}