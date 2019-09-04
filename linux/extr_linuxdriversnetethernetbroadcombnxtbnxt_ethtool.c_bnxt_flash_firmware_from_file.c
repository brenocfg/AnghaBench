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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX_DIR_ORDINAL_FIRST ; 
 int bnxt_dir_type_is_ape_bin_format (int /*<<< orphan*/ ) ; 
 int bnxt_dir_type_is_other_exec_format (int /*<<< orphan*/ ) ; 
 int bnxt_flash_firmware (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_flash_microcode (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_flash_nvram (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,char const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_flash_firmware_from_file(struct net_device *dev,
					 u16 dir_type,
					 const char *filename)
{
	const struct firmware  *fw;
	int			rc;

	rc = request_firmware(&fw, filename, &dev->dev);
	if (rc != 0) {
		netdev_err(dev, "Error %d requesting firmware file: %s\n",
			   rc, filename);
		return rc;
	}
	if (bnxt_dir_type_is_ape_bin_format(dir_type) == true)
		rc = bnxt_flash_firmware(dev, dir_type, fw->data, fw->size);
	else if (bnxt_dir_type_is_other_exec_format(dir_type) == true)
		rc = bnxt_flash_microcode(dev, dir_type, fw->data, fw->size);
	else
		rc = bnxt_flash_nvram(dev, dir_type, BNX_DIR_ORDINAL_FIRST,
				      0, 0, fw->data, fw->size);
	release_firmware(fw);
	return rc;
}