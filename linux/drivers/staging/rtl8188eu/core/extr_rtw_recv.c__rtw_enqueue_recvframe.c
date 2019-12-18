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
struct recv_frame {int /*<<< orphan*/  list; } ;
struct __queue {int dummy; } ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  get_list_head (struct __queue*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

int _rtw_enqueue_recvframe(struct recv_frame *precvframe, struct __queue *queue)
{
	list_del_init(&precvframe->list);
	list_add_tail(&precvframe->list, get_list_head(queue));

	return _SUCCESS;
}