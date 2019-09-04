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
struct TYPE_3__ {int* invoke_used; } ;
struct TYPE_4__ {TYPE_1__ dss1; } ;
struct PStack {TYPE_2__ prot; } ;

/* Variables and functions */

__attribute__((used)) static void free_invoke_id(struct PStack *p, unsigned char id)
{

	if (!id) return; /* 0 = invalid value */

	p->prot.dss1.invoke_used[id >> 3] &= ~(1 << (id & 7));
}