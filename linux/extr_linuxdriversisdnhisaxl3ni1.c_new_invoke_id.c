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
struct TYPE_3__ {int last_invoke_id; int* invoke_used; } ;
struct TYPE_4__ {TYPE_1__ ni1; } ;
struct PStack {TYPE_2__ prot; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char new_invoke_id(struct PStack *p)
{
	unsigned char retval;
	int i;

	i = 32; /* maximum search depth */

	retval = p->prot.ni1.last_invoke_id + 1; /* try new id */
	while ((i) && (p->prot.ni1.invoke_used[retval >> 3] == 0xFF)) {
		p->prot.ni1.last_invoke_id = (retval & 0xF8) + 8;
		i--;
	}
	if (i) {
		while (p->prot.ni1.invoke_used[retval >> 3] & (1 << (retval & 7)))
			retval++;
	} else
		retval = 0;
	p->prot.ni1.last_invoke_id = retval;
	p->prot.ni1.invoke_used[retval >> 3] |= (1 << (retval & 7));
	return (retval);
}