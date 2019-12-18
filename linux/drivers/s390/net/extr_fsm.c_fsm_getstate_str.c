#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* f; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ fsm_instance ;
struct TYPE_4__ {int nr_states; char const** state_names; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

const char *
fsm_getstate_str(fsm_instance *fi)
{
	int st = atomic_read(&fi->state);
	if (st >= fi->f->nr_states)
		return "Invalid";
	return fi->f->state_names[st];
}