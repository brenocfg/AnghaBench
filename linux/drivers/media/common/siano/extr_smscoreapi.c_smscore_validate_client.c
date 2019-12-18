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
struct smscore_idlist_t {int id; int data_type; int /*<<< orphan*/  entry; } ;
struct smscore_device_t {int /*<<< orphan*/  clientslock; } ;
struct smscore_client_t {int /*<<< orphan*/  idlist; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct smscore_idlist_t* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct smscore_client_t* smscore_find_client (struct smscore_device_t*,int,int) ; 

__attribute__((used)) static int smscore_validate_client(struct smscore_device_t *coredev,
				   struct smscore_client_t *client,
				   int data_type, int id)
{
	struct smscore_idlist_t *listentry;
	struct smscore_client_t *registered_client;

	if (!client) {
		pr_err("bad parameter.\n");
		return -EINVAL;
	}
	registered_client = smscore_find_client(coredev, data_type, id);
	if (registered_client == client)
		return 0;

	if (registered_client) {
		pr_err("The msg ID already registered to another client.\n");
		return -EEXIST;
	}
	listentry = kzalloc(sizeof(*listentry), GFP_KERNEL);
	if (!listentry)
		return -ENOMEM;

	listentry->id = id;
	listentry->data_type = data_type;
	list_add_locked(&listentry->entry, &client->idlist,
			&coredev->clientslock);
	return 0;
}