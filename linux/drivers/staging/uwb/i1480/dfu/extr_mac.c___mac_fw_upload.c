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
struct i1480 {int /*<<< orphan*/  dev; } ;
struct fw_hdr {int dummy; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,char const*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  fw_hdrs_free (struct fw_hdr*) ; 
 int fw_hdrs_load (struct i1480*,struct fw_hdr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mac_fw_hdrs_push (struct i1480*,struct fw_hdr*,char const*,char const*) ; 
 int /*<<< orphan*/  mac_fw_upload_disable (struct i1480*) ; 
 int mac_fw_upload_enable (struct i1480*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int __mac_fw_upload(struct i1480 *i1480, const char *fw_name,
		    const char *fw_tag)
{
	int result;
	const struct firmware *fw;
	struct fw_hdr *fw_hdrs;

	result = request_firmware(&fw, fw_name, i1480->dev);
	if (result < 0)	/* Up to caller to complain on -ENOENT */
		goto out;
	result = fw_hdrs_load(i1480, &fw_hdrs, fw->data, fw->size);
	if (result < 0) {
		dev_err(i1480->dev, "%s fw '%s': failed to parse firmware "
			"file: %d\n", fw_tag, fw_name, result);
		goto out_release;
	}
	result = mac_fw_upload_enable(i1480);
	if (result < 0)
		goto out_hdrs_release;
	result = mac_fw_hdrs_push(i1480, fw_hdrs, fw_name, fw_tag);
	mac_fw_upload_disable(i1480);
out_hdrs_release:
	if (result >= 0)
		dev_info(i1480->dev, "%s fw '%s': uploaded\n", fw_tag, fw_name);
	else
		dev_err(i1480->dev, "%s fw '%s': failed to upload (%d), "
			"power cycle device\n", fw_tag, fw_name, result);
	fw_hdrs_free(fw_hdrs);
out_release:
	release_firmware(fw);
out:
	return result;
}