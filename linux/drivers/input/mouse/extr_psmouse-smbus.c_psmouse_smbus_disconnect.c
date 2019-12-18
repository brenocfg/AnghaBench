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
struct psmouse_smbus_dev {int dead; TYPE_1__* client; int /*<<< orphan*/  psmouse; int /*<<< orphan*/  node; } ;
struct psmouse {struct psmouse_smbus_dev* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct psmouse_smbus_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psmouse_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_smbus_mutex ; 
 int /*<<< orphan*/  psmouse_smbus_schedule_remove (TYPE_1__*) ; 

__attribute__((used)) static void psmouse_smbus_disconnect(struct psmouse *psmouse)
{
	struct psmouse_smbus_dev *smbdev = psmouse->private;

	mutex_lock(&psmouse_smbus_mutex);

	if (smbdev->dead) {
		list_del(&smbdev->node);
		kfree(smbdev);
	} else {
		smbdev->dead = true;
		psmouse_dbg(smbdev->psmouse,
			    "posting removal request for SMBus companion %s\n",
			    dev_name(&smbdev->client->dev));
		psmouse_smbus_schedule_remove(smbdev->client);
	}

	mutex_unlock(&psmouse_smbus_mutex);

	psmouse->private = NULL;
}