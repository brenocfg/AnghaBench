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
struct firmware {int size; int* data; } ;
struct cas {scalar_t__ phy_id; int fw_load_addr; int fw_size; int /*<<< orphan*/  fw_data; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PHY_NS_DP83065 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmalloc (int) ; 

__attribute__((used)) static void cas_saturn_firmware_init(struct cas *cp)
{
	const struct firmware *fw;
	const char fw_name[] = "sun/cassini.bin";
	int err;

	if (PHY_NS_DP83065 != cp->phy_id)
		return;

	err = request_firmware(&fw, fw_name, &cp->pdev->dev);
	if (err) {
		pr_err("Failed to load firmware \"%s\"\n",
		       fw_name);
		return;
	}
	if (fw->size < 2) {
		pr_err("bogus length %zu in \"%s\"\n",
		       fw->size, fw_name);
		goto out;
	}
	cp->fw_load_addr= fw->data[1] << 8 | fw->data[0];
	cp->fw_size = fw->size - 2;
	cp->fw_data = vmalloc(cp->fw_size);
	if (!cp->fw_data)
		goto out;
	memcpy(cp->fw_data, &fw->data[2], cp->fw_size);
out:
	release_firmware(fw);
}