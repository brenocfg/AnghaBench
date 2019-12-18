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
struct TYPE_2__ {scalar_t__ major; scalar_t__ minor; int /*<<< orphan*/  build; } ;
struct i40e_client {int /*<<< orphan*/  name; TYPE_1__ version; } ;

/* Variables and functions */
 int EEXIST ; 
 int EIO ; 
 scalar_t__ I40E_CLIENT_VERSION_MAJOR ; 
 scalar_t__ I40E_CLIENT_VERSION_MINOR ; 
 int /*<<< orphan*/  i40e_client_interface_version_str ; 
 int /*<<< orphan*/  i40e_client_prepare (struct i40e_client*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 struct i40e_client* registered_client ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int i40e_register_client(struct i40e_client *client)
{
	int ret = 0;

	if (!client) {
		ret = -EIO;
		goto out;
	}

	if (strlen(client->name) == 0) {
		pr_info("i40e: Failed to register client with no name\n");
		ret = -EIO;
		goto out;
	}

	if (registered_client) {
		pr_info("i40e: Client %s has already been registered!\n",
			client->name);
		ret = -EEXIST;
		goto out;
	}

	if ((client->version.major != I40E_CLIENT_VERSION_MAJOR) ||
	    (client->version.minor != I40E_CLIENT_VERSION_MINOR)) {
		pr_info("i40e: Failed to register client %s due to mismatched client interface version\n",
			client->name);
		pr_info("Client is using version: %02d.%02d.%02d while LAN driver supports %s\n",
			client->version.major, client->version.minor,
			client->version.build,
			i40e_client_interface_version_str);
		ret = -EIO;
		goto out;
	}

	registered_client = client;

	i40e_client_prepare(client);

	pr_info("i40e: Registered client %s\n", client->name);
out:
	return ret;
}