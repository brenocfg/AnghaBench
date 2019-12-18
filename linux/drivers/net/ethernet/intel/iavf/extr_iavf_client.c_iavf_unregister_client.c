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
struct iavf_client {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  iavf_client_release (struct iavf_client*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct iavf_client* vf_registered_client ; 

int iavf_unregister_client(struct iavf_client *client)
{
	int ret = 0;

	/* When a unregister request comes through we would have to send
	 * a close for each of the client instances that were opened.
	 * client_release function is called to handle this.
	 */
	iavf_client_release(client);

	if (vf_registered_client != client) {
		pr_info("iavf: Client %s has not been registered\n",
			client->name);
		ret = -ENODEV;
		goto out;
	}
	vf_registered_client = NULL;
	pr_info("iavf: Unregistered client %s\n", client->name);
out:
	return ret;
}