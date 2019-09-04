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
struct TYPE_2__ {int /*<<< orphan*/  (* l3l2 ) (struct PStack*,int,void*) ;} ;
struct PStack {TYPE_1__ l3; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct PStack*,int,void*) ; 

__attribute__((used)) static void
isdnl3_trans(struct PStack *st, int pr, void *arg) {
	st->l3.l3l2(st, pr, arg);
}