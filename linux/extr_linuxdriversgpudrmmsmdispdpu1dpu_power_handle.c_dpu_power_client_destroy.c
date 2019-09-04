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
struct dpu_power_handle {int /*<<< orphan*/  phandle_lock; } ;
struct dpu_power_client {int /*<<< orphan*/  list; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dpu_power_client*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,struct dpu_power_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void dpu_power_client_destroy(struct dpu_power_handle *phandle,
	struct dpu_power_client *client)
{
	if (!client  || !phandle) {
		pr_err("reg bus vote: invalid client handle\n");
	} else if (!client->active) {
		pr_err("dpu power deinit already done\n");
		kfree(client);
	} else {
		pr_debug("bus vote client %s destroyed:%pK id:%u\n",
			client->name, client, client->id);
		mutex_lock(&phandle->phandle_lock);
		list_del_init(&client->list);
		mutex_unlock(&phandle->phandle_lock);
		kfree(client);
	}
}