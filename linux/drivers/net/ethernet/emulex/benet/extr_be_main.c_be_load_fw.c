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
typedef  int /*<<< orphan*/  u8 ;
struct firmware {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  be_cmd_get_fw_ver (struct be_adapter*) ; 
 int be_fw_download (struct be_adapter*,struct firmware const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int lancer_fw_download (struct be_adapter*,struct firmware const*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int be_load_fw(struct be_adapter *adapter, u8 *fw_file)
{
	const struct firmware *fw;
	int status;

	if (!netif_running(adapter->netdev)) {
		dev_err(&adapter->pdev->dev,
			"Firmware load not allowed (interface is down)\n");
		return -ENETDOWN;
	}

	status = request_firmware(&fw, fw_file, &adapter->pdev->dev);
	if (status)
		goto fw_exit;

	dev_info(&adapter->pdev->dev, "Flashing firmware file %s\n", fw_file);

	if (lancer_chip(adapter))
		status = lancer_fw_download(adapter, fw);
	else
		status = be_fw_download(adapter, fw);

	if (!status)
		be_cmd_get_fw_ver(adapter);

fw_exit:
	release_firmware(fw);
	return status;
}