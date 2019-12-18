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
struct i2c_board_info {struct psmouse_smbus_dev* platform_data; } ;
struct psmouse_smbus_dev {int need_deactivate; int /*<<< orphan*/  node; struct i2c_board_info board; scalar_t__ client; struct psmouse* psmouse; } ;
struct psmouse {scalar_t__ resync_time; int /*<<< orphan*/  disconnect; void* fast_reconnect; void* reconnect; int /*<<< orphan*/  protocol_handler; struct psmouse_smbus_dev* private; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int i2c_for_each_dev (struct psmouse_smbus_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psmouse_smbus_dev*) ; 
 struct psmouse_smbus_dev* kmemdup (void const*,size_t,int /*<<< orphan*/ ) ; 
 struct psmouse_smbus_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_smbus_create_companion ; 
 int /*<<< orphan*/  psmouse_smbus_disconnect ; 
 int /*<<< orphan*/  psmouse_smbus_list ; 
 int /*<<< orphan*/  psmouse_smbus_mutex ; 
 int /*<<< orphan*/  psmouse_smbus_process_byte ; 
 void* psmouse_smbus_reconnect ; 

int psmouse_smbus_init(struct psmouse *psmouse,
		       const struct i2c_board_info *board,
		       const void *pdata, size_t pdata_size,
		       bool need_deactivate,
		       bool leave_breadcrumbs)
{
	struct psmouse_smbus_dev *smbdev;
	int error;

	smbdev = kzalloc(sizeof(*smbdev), GFP_KERNEL);
	if (!smbdev)
		return -ENOMEM;

	smbdev->psmouse = psmouse;
	smbdev->board = *board;
	smbdev->need_deactivate = need_deactivate;

	if (pdata) {
		smbdev->board.platform_data = kmemdup(pdata, pdata_size,
						      GFP_KERNEL);
		if (!smbdev->board.platform_data) {
			kfree(smbdev);
			return -ENOMEM;
		}
	}

	if (need_deactivate)
		psmouse_deactivate(psmouse);

	psmouse->private = smbdev;
	psmouse->protocol_handler = psmouse_smbus_process_byte;
	psmouse->reconnect = psmouse_smbus_reconnect;
	psmouse->fast_reconnect = psmouse_smbus_reconnect;
	psmouse->disconnect = psmouse_smbus_disconnect;
	psmouse->resync_time = 0;

	mutex_lock(&psmouse_smbus_mutex);
	list_add_tail(&smbdev->node, &psmouse_smbus_list);
	mutex_unlock(&psmouse_smbus_mutex);

	/* Bind to already existing adapters right away */
	error = i2c_for_each_dev(smbdev, psmouse_smbus_create_companion);

	if (smbdev->client) {
		/* We have our companion device */
		return 0;
	}

	/*
	 * If we did not create i2c device we will not need platform
	 * data even if we are leaving breadcrumbs.
	 */
	kfree(smbdev->board.platform_data);
	smbdev->board.platform_data = NULL;

	if (error < 0 || !leave_breadcrumbs) {
		mutex_lock(&psmouse_smbus_mutex);
		list_del(&smbdev->node);
		mutex_unlock(&psmouse_smbus_mutex);

		kfree(smbdev);
	}

	return error < 0 ? error : -EAGAIN;
}