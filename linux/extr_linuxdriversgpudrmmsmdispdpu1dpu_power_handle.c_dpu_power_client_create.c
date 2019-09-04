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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_power_handle {int /*<<< orphan*/  phandle_lock; int /*<<< orphan*/  power_client_clist; } ;
struct dpu_power_client {int active; int /*<<< orphan*/  list; int /*<<< orphan*/  id; int /*<<< orphan*/  usecase_ndx; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dpu_power_client* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_CLIENT_NAME_LEN ; 
 int /*<<< orphan*/  VOTE_INDEX_DISABLE ; 
 struct dpu_power_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,struct dpu_power_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct dpu_power_client *dpu_power_client_create(
	struct dpu_power_handle *phandle, char *client_name)
{
	struct dpu_power_client *client;
	static u32 id;

	if (!client_name || !phandle) {
		pr_err("client name is null or invalid power data\n");
		return ERR_PTR(-EINVAL);
	}

	client = kzalloc(sizeof(struct dpu_power_client), GFP_KERNEL);
	if (!client)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&phandle->phandle_lock);
	strlcpy(client->name, client_name, MAX_CLIENT_NAME_LEN);
	client->usecase_ndx = VOTE_INDEX_DISABLE;
	client->id = id;
	client->active = true;
	pr_debug("client %s created:%pK id :%d\n", client_name,
		client, id);
	id++;
	list_add(&client->list, &phandle->power_client_clist);
	mutex_unlock(&phandle->phandle_lock);

	return client;
}