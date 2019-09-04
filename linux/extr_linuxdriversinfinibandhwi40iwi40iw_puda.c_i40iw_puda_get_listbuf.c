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
struct list_head {scalar_t__ next; } ;
struct i40iw_puda_buf {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

__attribute__((used)) static struct i40iw_puda_buf *i40iw_puda_get_listbuf(struct list_head *list)
{
	struct i40iw_puda_buf *buf = NULL;

	if (!list_empty(list)) {
		buf = (struct i40iw_puda_buf *)list->next;
		list_del((struct list_head *)&buf->list);
	}
	return buf;
}