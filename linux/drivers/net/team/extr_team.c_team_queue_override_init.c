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
struct team {struct list_head* qom_lists; TYPE_1__* dev; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int num_tx_queues; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct list_head* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int team_queue_override_init(struct team *team)
{
	struct list_head *listarr;
	unsigned int queue_cnt = team->dev->num_tx_queues - 1;
	unsigned int i;

	if (!queue_cnt)
		return 0;
	listarr = kmalloc_array(queue_cnt, sizeof(struct list_head),
				GFP_KERNEL);
	if (!listarr)
		return -ENOMEM;
	team->qom_lists = listarr;
	for (i = 0; i < queue_cnt; i++)
		INIT_LIST_HEAD(listarr++);
	return 0;
}