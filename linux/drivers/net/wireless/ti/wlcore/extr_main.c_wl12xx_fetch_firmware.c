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
struct wl1271 {char* plt_fw_name; int last_vif_count; char* mr_fw_name; char* sr_fw_name; int fw_type; int fw_len; int /*<<< orphan*/  fw; int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
typedef  enum wl12xx_fw_type { ____Placeholder_wl12xx_fw_type } wl12xx_fw_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int EILSEQ ; 
 int ENOMEM ; 
 int WL12XX_FW_TYPE_MULTI ; 
 int WL12XX_FW_TYPE_NONE ; 
 int WL12XX_FW_TYPE_NORMAL ; 
 int WL12XX_FW_TYPE_PLT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 

__attribute__((used)) static int wl12xx_fetch_firmware(struct wl1271 *wl, bool plt)
{
	const struct firmware *fw;
	const char *fw_name;
	enum wl12xx_fw_type fw_type;
	int ret;

	if (plt) {
		fw_type = WL12XX_FW_TYPE_PLT;
		fw_name = wl->plt_fw_name;
	} else {
		/*
		 * we can't call wl12xx_get_vif_count() here because
		 * wl->mutex is taken, so use the cached last_vif_count value
		 */
		if (wl->last_vif_count > 1 && wl->mr_fw_name) {
			fw_type = WL12XX_FW_TYPE_MULTI;
			fw_name = wl->mr_fw_name;
		} else {
			fw_type = WL12XX_FW_TYPE_NORMAL;
			fw_name = wl->sr_fw_name;
		}
	}

	if (wl->fw_type == fw_type)
		return 0;

	wl1271_debug(DEBUG_BOOT, "booting firmware %s", fw_name);

	ret = request_firmware(&fw, fw_name, wl->dev);

	if (ret < 0) {
		wl1271_error("could not get firmware %s: %d", fw_name, ret);
		return ret;
	}

	if (fw->size % 4) {
		wl1271_error("firmware size is not multiple of 32 bits: %zu",
			     fw->size);
		ret = -EILSEQ;
		goto out;
	}

	vfree(wl->fw);
	wl->fw_type = WL12XX_FW_TYPE_NONE;
	wl->fw_len = fw->size;
	wl->fw = vmalloc(wl->fw_len);

	if (!wl->fw) {
		wl1271_error("could not allocate memory for the firmware");
		ret = -ENOMEM;
		goto out;
	}

	memcpy(wl->fw, fw->data, wl->fw_len);
	ret = 0;
	wl->fw_type = fw_type;
out:
	release_firmware(fw);

	return ret;
}