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
struct TYPE_2__ {struct list_head* next; } ;
struct wil6210_vif {int /*<<< orphan*/  probe_client_mutex; TYPE_1__ probe_client_pending; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (struct list_head*) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct list_head *next_probe_client(struct wil6210_vif *vif)
{
	struct list_head *ret = NULL;

	mutex_lock(&vif->probe_client_mutex);

	if (!list_empty(&vif->probe_client_pending)) {
		ret = vif->probe_client_pending.next;
		list_del(ret);
	}

	mutex_unlock(&vif->probe_client_mutex);

	return ret;
}