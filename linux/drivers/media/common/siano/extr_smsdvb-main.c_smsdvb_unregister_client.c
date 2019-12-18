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
struct smsdvb_client_t {int /*<<< orphan*/  adapter; int /*<<< orphan*/  demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  frontend; int /*<<< orphan*/  smsclient; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct smsdvb_client_t*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smscore_unregister_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsdvb_debugfs_release (struct smsdvb_client_t*) ; 
 int /*<<< orphan*/  smsdvb_media_device_unregister (struct smsdvb_client_t*) ; 

__attribute__((used)) static void smsdvb_unregister_client(struct smsdvb_client_t *client)
{
	/* must be called under clientslock */

	list_del(&client->entry);

	smsdvb_debugfs_release(client);
	smscore_unregister_client(client->smsclient);
	dvb_unregister_frontend(&client->frontend);
	dvb_dmxdev_release(&client->dmxdev);
	dvb_dmx_release(&client->demux);
	smsdvb_media_device_unregister(client);
	dvb_unregister_adapter(&client->adapter);
	kfree(client);
}