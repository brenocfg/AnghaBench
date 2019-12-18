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
struct nfc_dev {int dummy; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_NCI_DEVICE_MGNT_GATE ; 
 int /*<<< orphan*/  ST_NCI_HCI_DM_FWUPD_STOP ; 
 int nci_hci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 

__attribute__((used)) static int st_nci_hci_dm_fwupd_end(struct nfc_dev *dev, void *data,
				   size_t data_len)
{
	struct nci_dev *ndev = nfc_get_drvdata(dev);

	return nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_HCI_DM_FWUPD_STOP, data, data_len, NULL);
}