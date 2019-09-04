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
typedef  int u16 ;
struct go7007 {int boot_fw_len; int /*<<< orphan*/ * boot_fw; int /*<<< orphan*/  dev; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ go7007_interface_reset (struct go7007*) ; 
 scalar_t__ go7007_read_interrupt (struct go7007*,int*,int*) ; 
 scalar_t__ go7007_send_firmware (struct go7007*,int /*<<< orphan*/ *,int) ; 
 void* kmemdup (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (struct go7007*,char*,...) ; 

__attribute__((used)) static int go7007_load_encoder(struct go7007 *go)
{
	const struct firmware *fw_entry;
	char fw_name[] = "go7007/go7007fw.bin";
	void *bounce;
	int fw_len, rv = 0;
	u16 intr_val, intr_data;

	if (go->boot_fw == NULL) {
		if (request_firmware(&fw_entry, fw_name, go->dev)) {
			v4l2_err(go, "unable to load firmware from file \"%s\"\n", fw_name);
			return -1;
		}
		if (fw_entry->size < 16 || memcmp(fw_entry->data, "WISGO7007FW", 11)) {
			v4l2_err(go, "file \"%s\" does not appear to be go7007 firmware\n", fw_name);
			release_firmware(fw_entry);
			return -1;
		}
		fw_len = fw_entry->size - 16;
		bounce = kmemdup(fw_entry->data + 16, fw_len, GFP_KERNEL);
		if (bounce == NULL) {
			v4l2_err(go, "unable to allocate %d bytes for firmware transfer\n", fw_len);
			release_firmware(fw_entry);
			return -1;
		}
		release_firmware(fw_entry);
		go->boot_fw_len = fw_len;
		go->boot_fw = bounce;
	}
	if (go7007_interface_reset(go) < 0 ||
	    go7007_send_firmware(go, go->boot_fw, go->boot_fw_len) < 0 ||
	    go7007_read_interrupt(go, &intr_val, &intr_data) < 0 ||
			(intr_val & ~0x1) != 0x5a5a) {
		v4l2_err(go, "error transferring firmware\n");
		rv = -1;
	}
	return rv;
}