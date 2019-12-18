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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct tb_switch {int /*<<< orphan*/ * drom; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; scalar_t__ uid; TYPE_1__* ports; } ;
struct tb_drom_header {int data_len; scalar_t__ uid_crc8; scalar_t__ data_crc32; int device_rom_revision; int /*<<< orphan*/  model_id; int /*<<< orphan*/  vendor_id; scalar_t__ uid; } ;
struct TYPE_2__ {int link_nr; struct TYPE_2__* dual_link_port; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TB_DROM_DATA_START ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ tb_crc32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tb_crc8 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tb_drom_copy_efi (struct tb_switch*,int*) ; 
 scalar_t__ tb_drom_copy_nvm (struct tb_switch*,int*) ; 
 int tb_drom_parse_entries (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_drom_read_uid_only (struct tb_switch*,scalar_t__*) ; 
 int tb_eeprom_get_drom_offset (struct tb_switch*,int*) ; 
 int tb_eeprom_read_n (struct tb_switch*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_sw_dbg (struct tb_switch*,char*,int) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*,...) ; 

int tb_drom_read(struct tb_switch *sw)
{
	u16 drom_offset;
	u16 size;
	u32 crc;
	struct tb_drom_header *header;
	int res;
	if (sw->drom)
		return 0;

	if (tb_route(sw) == 0) {
		/*
		 * Apple's NHI EFI driver supplies a DROM for the root switch
		 * in a device property. Use it if available.
		 */
		if (tb_drom_copy_efi(sw, &size) == 0)
			goto parse;

		/* Non-Apple hardware has the DROM as part of NVM */
		if (tb_drom_copy_nvm(sw, &size) == 0)
			goto parse;

		/*
		 * The root switch contains only a dummy drom (header only,
		 * no entries). Hardcode the configuration here.
		 */
		tb_drom_read_uid_only(sw, &sw->uid);

		sw->ports[1].link_nr = 0;
		sw->ports[2].link_nr = 1;
		sw->ports[1].dual_link_port = &sw->ports[2];
		sw->ports[2].dual_link_port = &sw->ports[1];

		sw->ports[3].link_nr = 0;
		sw->ports[4].link_nr = 1;
		sw->ports[3].dual_link_port = &sw->ports[4];
		sw->ports[4].dual_link_port = &sw->ports[3];

		return 0;
	}

	res = tb_eeprom_get_drom_offset(sw, &drom_offset);
	if (res)
		return res;

	res = tb_eeprom_read_n(sw, drom_offset + 14, (u8 *) &size, 2);
	if (res)
		return res;
	size &= 0x3ff;
	size += TB_DROM_DATA_START;
	tb_sw_dbg(sw, "reading drom (length: %#x)\n", size);
	if (size < sizeof(*header)) {
		tb_sw_warn(sw, "drom too small, aborting\n");
		return -EIO;
	}

	sw->drom = kzalloc(size, GFP_KERNEL);
	if (!sw->drom)
		return -ENOMEM;
	res = tb_eeprom_read_n(sw, drom_offset, sw->drom, size);
	if (res)
		goto err;

parse:
	header = (void *) sw->drom;

	if (header->data_len + TB_DROM_DATA_START != size) {
		tb_sw_warn(sw, "drom size mismatch, aborting\n");
		goto err;
	}

	crc = tb_crc8((u8 *) &header->uid, 8);
	if (crc != header->uid_crc8) {
		tb_sw_warn(sw,
			"drom uid crc8 mismatch (expected: %#x, got: %#x), aborting\n",
			header->uid_crc8, crc);
		goto err;
	}
	if (!sw->uid)
		sw->uid = header->uid;
	sw->vendor = header->vendor_id;
	sw->device = header->model_id;

	crc = tb_crc32(sw->drom + TB_DROM_DATA_START, header->data_len);
	if (crc != header->data_crc32) {
		tb_sw_warn(sw,
			"drom data crc32 mismatch (expected: %#x, got: %#x), continuing\n",
			header->data_crc32, crc);
	}

	if (header->device_rom_revision > 2)
		tb_sw_warn(sw, "drom device_rom_revision %#x unknown\n",
			header->device_rom_revision);

	return tb_drom_parse_entries(sw);
err:
	kfree(sw->drom);
	sw->drom = NULL;
	return -EIO;

}