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
struct smscore_device_t {int /*<<< orphan*/  clientslock; int /*<<< orphan*/  clients; } ;
struct smscore_client_t {int /*<<< orphan*/  entry; int /*<<< orphan*/  context; int /*<<< orphan*/  onremove_handler; int /*<<< orphan*/  onresponse_handler; struct smscore_device_t* coredev; int /*<<< orphan*/  idlist; } ;
struct smsclient_params_t {int /*<<< orphan*/  initial_id; int /*<<< orphan*/  data_type; int /*<<< orphan*/  context; int /*<<< orphan*/  onremove_handler; int /*<<< orphan*/  onresponse_handler; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct smscore_client_t* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ smscore_find_client (struct smscore_device_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_validate_client (struct smscore_device_t*,struct smscore_client_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smscore_register_client(struct smscore_device_t *coredev,
			    struct smsclient_params_t *params,
			    struct smscore_client_t **client)
{
	struct smscore_client_t *newclient;
	/* check that no other channel with same parameters exists */
	if (smscore_find_client(coredev, params->data_type,
				params->initial_id)) {
		pr_err("Client already exist.\n");
		return -EEXIST;
	}

	newclient = kzalloc(sizeof(*newclient), GFP_KERNEL);
	if (!newclient)
		return -ENOMEM;

	INIT_LIST_HEAD(&newclient->idlist);
	newclient->coredev = coredev;
	newclient->onresponse_handler = params->onresponse_handler;
	newclient->onremove_handler = params->onremove_handler;
	newclient->context = params->context;
	list_add_locked(&newclient->entry, &coredev->clients,
			&coredev->clientslock);
	smscore_validate_client(coredev, newclient, params->data_type,
				params->initial_id);
	*client = newclient;
	pr_debug("%p %d %d\n", params->context, params->data_type,
		  params->initial_id);

	return 0;
}