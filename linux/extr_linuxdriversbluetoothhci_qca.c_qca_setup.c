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
struct qca_serdev {scalar_t__ btsoc_type; } ;
struct qca_data {int /*<<< orphan*/  flags; } ;
struct hci_uart {struct hci_dev* hdev; int /*<<< orphan*/  serdev; struct qca_data* priv; } ;
struct hci_dev {int /*<<< orphan*/  set_bdaddr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 unsigned int QCA_BAUDRATE_115200 ; 
 int /*<<< orphan*/  QCA_INIT_SPEED ; 
 int /*<<< orphan*/  QCA_OPER_SPEED ; 
 scalar_t__ QCA_WCN3990 ; 
 int /*<<< orphan*/  STATE_IN_BAND_SLEEP_ENABLED ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qca_check_speeds (struct hci_uart*) ; 
 int /*<<< orphan*/  qca_debugfs_init (struct hci_dev*) ; 
 unsigned int qca_get_baudrate_value (unsigned int) ; 
 unsigned int qca_get_speed (struct hci_uart*,int /*<<< orphan*/ ) ; 
 int qca_read_soc_version (struct hci_dev*,int*) ; 
 int /*<<< orphan*/  qca_set_bdaddr_rome ; 
 int qca_set_speed (struct hci_uart*,int /*<<< orphan*/ ) ; 
 int qca_uart_setup (struct hci_dev*,unsigned int,scalar_t__,int) ; 
 int qca_wcn3990_init (struct hci_uart*) ; 
 struct qca_serdev* serdev_device_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qca_setup(struct hci_uart *hu)
{
	struct hci_dev *hdev = hu->hdev;
	struct qca_data *qca = hu->priv;
	unsigned int speed, qca_baudrate = QCA_BAUDRATE_115200;
	struct qca_serdev *qcadev;
	int ret;
	int soc_ver = 0;

	qcadev = serdev_device_get_drvdata(hu->serdev);

	ret = qca_check_speeds(hu);
	if (ret)
		return ret;

	/* Patch downloading has to be done without IBS mode */
	clear_bit(STATE_IN_BAND_SLEEP_ENABLED, &qca->flags);

	if (qcadev->btsoc_type == QCA_WCN3990) {
		bt_dev_info(hdev, "setting up wcn3990");
		ret = qca_wcn3990_init(hu);
		if (ret)
			return ret;

		ret = qca_read_soc_version(hdev, &soc_ver);
		if (ret)
			return ret;
	} else {
		bt_dev_info(hdev, "ROME setup");
		qca_set_speed(hu, QCA_INIT_SPEED);
	}

	/* Setup user speed if needed */
	speed = qca_get_speed(hu, QCA_OPER_SPEED);
	if (speed) {
		ret = qca_set_speed(hu, QCA_OPER_SPEED);
		if (ret)
			return ret;

		qca_baudrate = qca_get_baudrate_value(speed);
	}

	if (qcadev->btsoc_type != QCA_WCN3990) {
		/* Get QCA version information */
		ret = qca_read_soc_version(hdev, &soc_ver);
		if (ret)
			return ret;
	}

	bt_dev_info(hdev, "QCA controller version 0x%08x", soc_ver);
	/* Setup patch / NVM configurations */
	ret = qca_uart_setup(hdev, qca_baudrate, qcadev->btsoc_type, soc_ver);
	if (!ret) {
		set_bit(STATE_IN_BAND_SLEEP_ENABLED, &qca->flags);
		qca_debugfs_init(hdev);
	} else if (ret == -ENOENT) {
		/* No patch/nvm-config found, run with original fw/config */
		ret = 0;
	} else if (ret == -EAGAIN) {
		/*
		 * Userspace firmware loader will return -EAGAIN in case no
		 * patch/nvm-config is found, so run with original fw/config.
		 */
		ret = 0;
	}

	/* Setup bdaddr */
	hu->hdev->set_bdaddr = qca_set_bdaddr_rome;

	return ret;
}