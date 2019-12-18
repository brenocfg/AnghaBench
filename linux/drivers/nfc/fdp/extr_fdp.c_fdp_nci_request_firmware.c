#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nci_dev {int dummy; } ;
struct fdp_nci_info {int ram_patch_version; int otp_patch_version; TYPE_3__* otp_patch; TYPE_3__* ram_patch; TYPE_2__* phy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {scalar_t__ size; scalar_t__ data; } ;
struct TYPE_5__ {TYPE_1__* i2c_dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 size_t FDP_FW_HEADER_SIZE ; 
 int /*<<< orphan*/  FDP_OTP_PATCH_NAME ; 
 int /*<<< orphan*/  FDP_RAM_PATCH_NAME ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 struct fdp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nfc_err (struct device*,char*) ; 
 int request_firmware (TYPE_3__**,int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static int fdp_nci_request_firmware(struct nci_dev *ndev)
{
	struct fdp_nci_info *info = nci_get_drvdata(ndev);
	struct device *dev = &info->phy->i2c_dev->dev;
	u8 *data;
	int r;

	r = request_firmware(&info->ram_patch, FDP_RAM_PATCH_NAME, dev);
	if (r < 0) {
		nfc_err(dev, "RAM patch request error\n");
		goto error;
	}

	data = (u8 *) info->ram_patch->data;
	info->ram_patch_version =
		data[FDP_FW_HEADER_SIZE] |
		(data[FDP_FW_HEADER_SIZE + 1] << 8) |
		(data[FDP_FW_HEADER_SIZE + 2] << 16) |
		(data[FDP_FW_HEADER_SIZE + 3] << 24);

	dev_dbg(dev, "RAM patch version: %d, size: %d\n",
		  info->ram_patch_version, (int) info->ram_patch->size);


	r = request_firmware(&info->otp_patch, FDP_OTP_PATCH_NAME, dev);
	if (r < 0) {
		nfc_err(dev, "OTP patch request error\n");
		goto out;
	}

	data = (u8 *) info->otp_patch->data;
	info->otp_patch_version =
		data[FDP_FW_HEADER_SIZE] |
		(data[FDP_FW_HEADER_SIZE + 1] << 8) |
		(data[FDP_FW_HEADER_SIZE+2] << 16) |
		(data[FDP_FW_HEADER_SIZE+3] << 24);

	dev_dbg(dev, "OTP patch version: %d, size: %d\n",
		 info->otp_patch_version, (int) info->otp_patch->size);
out:
	return 0;
error:
	return r;
}