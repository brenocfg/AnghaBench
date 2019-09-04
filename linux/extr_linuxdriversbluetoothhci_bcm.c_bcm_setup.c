#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hci_uart {int init_speed; int oper_speed; TYPE_2__* hdev; TYPE_1__* proto; struct bcm_data* priv; } ;
struct firmware {int dummy; } ;
struct bcm_data {int dummy; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  set_bdaddr; int /*<<< orphan*/  set_diag; } ;
struct TYPE_7__ {int init_speed; int oper_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_request_irq (struct bcm_data*) ; 
 int bcm_set_baudrate (struct hci_uart*,unsigned int) ; 
 int /*<<< orphan*/  bcm_set_diag ; 
 int bcm_setup_sleep (struct hci_uart*) ; 
 int /*<<< orphan*/  bt_dev_dbg (TYPE_2__*,char*,struct hci_uart*) ; 
 int /*<<< orphan*/  bt_dev_info (TYPE_2__*,char*,...) ; 
 int btbcm_finalize (TYPE_2__*) ; 
 int btbcm_initialize (TYPE_2__*,char*,int,int) ; 
 int btbcm_patchram (TYPE_2__*,struct firmware const*) ; 
 int /*<<< orphan*/  btbcm_set_bdaddr ; 
 int /*<<< orphan*/  host_set_baudrate (struct hci_uart*,unsigned int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_setup(struct hci_uart *hu)
{
	struct bcm_data *bcm = hu->priv;
	char fw_name[64];
	const struct firmware *fw;
	unsigned int speed;
	int err;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	hu->hdev->set_diag = bcm_set_diag;
	hu->hdev->set_bdaddr = btbcm_set_bdaddr;

	err = btbcm_initialize(hu->hdev, fw_name, sizeof(fw_name), false);
	if (err)
		return err;

	err = request_firmware(&fw, fw_name, &hu->hdev->dev);
	if (err < 0) {
		bt_dev_info(hu->hdev, "BCM: Patch %s not found", fw_name);
		return 0;
	}

	err = btbcm_patchram(hu->hdev, fw);
	if (err) {
		bt_dev_info(hu->hdev, "BCM: Patch failed (%d)", err);
		goto finalize;
	}

	/* Init speed if any */
	if (hu->init_speed)
		speed = hu->init_speed;
	else if (hu->proto->init_speed)
		speed = hu->proto->init_speed;
	else
		speed = 0;

	if (speed)
		host_set_baudrate(hu, speed);

	/* Operational speed if any */
	if (hu->oper_speed)
		speed = hu->oper_speed;
	else if (hu->proto->oper_speed)
		speed = hu->proto->oper_speed;
	else
		speed = 0;

	if (speed) {
		err = bcm_set_baudrate(hu, speed);
		if (!err)
			host_set_baudrate(hu, speed);
	}

finalize:
	release_firmware(fw);

	err = btbcm_finalize(hu->hdev);
	if (err)
		return err;

	if (!bcm_request_irq(bcm))
		err = bcm_setup_sleep(hu);

	return err;
}