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
struct i40e_client {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  i40e_client_release (struct i40e_client*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct i40e_client* registered_client ; 

int i40e_unregister_client(struct i40e_client *client)
{
	int ret = 0;

	if (registered_client != client) {
		pr_info("i40e: Client %s has not been registered\n",
			client->name);
		ret = -ENODEV;
		goto out;
	}
	registered_client = NULL;
	/* When a unregister request comes through we would have to send
	 * a close for each of the client instances that were opened.
	 * client_release function is called to handle this.
	 */
	i40e_client_release(client);

	pr_info("i40e: Unregistered client %s\n", client->name);
out:
	return ret;
}