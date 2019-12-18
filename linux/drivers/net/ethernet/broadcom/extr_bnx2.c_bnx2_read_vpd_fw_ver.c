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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2 {char* fw_version; } ;

/* Variables and functions */
 unsigned int BNX2_MAX_VER_SLEN ; 
 int BNX2_VPD_LEN ; 
 int /*<<< orphan*/  BNX2_VPD_NVRAM_OFFSET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PCI_VPD_INFO_FLD_HDR_SIZE ; 
 int /*<<< orphan*/  PCI_VPD_LRDT_RO_DATA ; 
 scalar_t__ PCI_VPD_LRDT_TAG_SIZE ; 
 int /*<<< orphan*/  PCI_VPD_RO_KEYWORD_MFR_ID ; 
 int /*<<< orphan*/  PCI_VPD_RO_KEYWORD_VENDOR0 ; 
 int bnx2_nvram_read (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,unsigned int) ; 
 int pci_vpd_find_info_keyword (int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ ) ; 
 int pci_vpd_find_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int pci_vpd_info_field_size (int /*<<< orphan*/ *) ; 
 unsigned int pci_vpd_lrdt_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2_read_vpd_fw_ver(struct bnx2 *bp)
{
	int rc, i, j;
	u8 *data;
	unsigned int block_end, rosize, len;

#define BNX2_VPD_NVRAM_OFFSET	0x300
#define BNX2_VPD_LEN		128
#define BNX2_MAX_VER_SLEN	30

	data = kmalloc(256, GFP_KERNEL);
	if (!data)
		return;

	rc = bnx2_nvram_read(bp, BNX2_VPD_NVRAM_OFFSET, data + BNX2_VPD_LEN,
			     BNX2_VPD_LEN);
	if (rc)
		goto vpd_done;

	for (i = 0; i < BNX2_VPD_LEN; i += 4) {
		data[i] = data[i + BNX2_VPD_LEN + 3];
		data[i + 1] = data[i + BNX2_VPD_LEN + 2];
		data[i + 2] = data[i + BNX2_VPD_LEN + 1];
		data[i + 3] = data[i + BNX2_VPD_LEN];
	}

	i = pci_vpd_find_tag(data, 0, BNX2_VPD_LEN, PCI_VPD_LRDT_RO_DATA);
	if (i < 0)
		goto vpd_done;

	rosize = pci_vpd_lrdt_size(&data[i]);
	i += PCI_VPD_LRDT_TAG_SIZE;
	block_end = i + rosize;

	if (block_end > BNX2_VPD_LEN)
		goto vpd_done;

	j = pci_vpd_find_info_keyword(data, i, rosize,
				      PCI_VPD_RO_KEYWORD_MFR_ID);
	if (j < 0)
		goto vpd_done;

	len = pci_vpd_info_field_size(&data[j]);

	j += PCI_VPD_INFO_FLD_HDR_SIZE;
	if (j + len > block_end || len != 4 ||
	    memcmp(&data[j], "1028", 4))
		goto vpd_done;

	j = pci_vpd_find_info_keyword(data, i, rosize,
				      PCI_VPD_RO_KEYWORD_VENDOR0);
	if (j < 0)
		goto vpd_done;

	len = pci_vpd_info_field_size(&data[j]);

	j += PCI_VPD_INFO_FLD_HDR_SIZE;
	if (j + len > block_end || len > BNX2_MAX_VER_SLEN)
		goto vpd_done;

	memcpy(bp->fw_version, &data[j], len);
	bp->fw_version[len] = ' ';

vpd_done:
	kfree(data);
}