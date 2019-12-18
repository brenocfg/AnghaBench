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
struct TYPE_2__ {struct mei_cl_cb* data; } ;
struct mei_cl_cb {TYPE_1__ buf; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mei_cl_cb*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void mei_io_cb_free(struct mei_cl_cb *cb)
{
	if (cb == NULL)
		return;

	list_del(&cb->list);
	kfree(cb->buf.data);
	kfree(cb);
}