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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct firmware {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIRMWARE_NAME ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  R128_PM4_MICROCODE_ADDR ; 
 int /*<<< orphan*/  R128_PM4_MICROCODE_DATAH ; 
 int /*<<< orphan*/  R128_PM4_MICROCODE_DATAL ; 
 int /*<<< orphan*/  R128_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 struct platform_device* platform_device_register_simple (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  r128_do_wait_for_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r128_cce_load_microcode(drm_r128_private_t *dev_priv)
{
	struct platform_device *pdev;
	const struct firmware *fw;
	const __be32 *fw_data;
	int rc, i;

	DRM_DEBUG("\n");

	pdev = platform_device_register_simple("r128_cce", 0, NULL, 0);
	if (IS_ERR(pdev)) {
		pr_err("r128_cce: Failed to register firmware\n");
		return PTR_ERR(pdev);
	}
	rc = request_firmware(&fw, FIRMWARE_NAME, &pdev->dev);
	platform_device_unregister(pdev);
	if (rc) {
		pr_err("r128_cce: Failed to load firmware \"%s\"\n",
		       FIRMWARE_NAME);
		return rc;
	}

	if (fw->size != 256 * 8) {
		pr_err("r128_cce: Bogus length %zu in firmware \"%s\"\n",
		       fw->size, FIRMWARE_NAME);
		rc = -EINVAL;
		goto out_release;
	}

	r128_do_wait_for_idle(dev_priv);

	fw_data = (const __be32 *)fw->data;
	R128_WRITE(R128_PM4_MICROCODE_ADDR, 0);
	for (i = 0; i < 256; i++) {
		R128_WRITE(R128_PM4_MICROCODE_DATAH,
			   be32_to_cpup(&fw_data[i * 2]));
		R128_WRITE(R128_PM4_MICROCODE_DATAL,
			   be32_to_cpup(&fw_data[i * 2 + 1]));
	}

out_release:
	release_firmware(fw);
	return rc;
}