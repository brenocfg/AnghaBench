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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* mdev; } ;
struct media_link {TYPE_2__ graph_obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  graph_mutex; } ;

/* Variables and functions */
 int __media_entity_setup_link (struct media_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int media_entity_setup_link(struct media_link *link, u32 flags)
{
	int ret;

	mutex_lock(&link->graph_obj.mdev->graph_mutex);
	ret = __media_entity_setup_link(link, flags);
	mutex_unlock(&link->graph_obj.mdev->graph_mutex);

	return ret;
}