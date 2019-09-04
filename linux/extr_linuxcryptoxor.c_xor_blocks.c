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
struct TYPE_2__ {int /*<<< orphan*/  (* do_5 ) (unsigned int,void*,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ;int /*<<< orphan*/  (* do_4 ) (unsigned int,void*,unsigned long*,unsigned long*,unsigned long*) ;int /*<<< orphan*/  (* do_3 ) (unsigned int,void*,unsigned long*,unsigned long*) ;int /*<<< orphan*/  (* do_2 ) (unsigned int,void*,unsigned long*) ;} ;

/* Variables and functions */
 TYPE_1__* active_template ; 
 int /*<<< orphan*/  stub1 (unsigned int,void*,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (unsigned int,void*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  stub3 (unsigned int,void*,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  stub4 (unsigned int,void*,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 

void
xor_blocks(unsigned int src_count, unsigned int bytes, void *dest, void **srcs)
{
	unsigned long *p1, *p2, *p3, *p4;

	p1 = (unsigned long *) srcs[0];
	if (src_count == 1) {
		active_template->do_2(bytes, dest, p1);
		return;
	}

	p2 = (unsigned long *) srcs[1];
	if (src_count == 2) {
		active_template->do_3(bytes, dest, p1, p2);
		return;
	}

	p3 = (unsigned long *) srcs[2];
	if (src_count == 3) {
		active_template->do_4(bytes, dest, p1, p2, p3);
		return;
	}

	p4 = (unsigned long *) srcs[3];
	active_template->do_5(bytes, dest, p1, p2, p3, p4);
}