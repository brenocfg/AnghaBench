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
struct TYPE_2__ {int /*<<< orphan*/  l3l2; } ;
struct PStack {TYPE_1__ l3; } ;

/* Variables and functions */
 int /*<<< orphan*/  transl2_l3l2 ; 

void
setstack_transl2(struct PStack *st)
{
	st->l3.l3l2 = transl2_l3l2;
}