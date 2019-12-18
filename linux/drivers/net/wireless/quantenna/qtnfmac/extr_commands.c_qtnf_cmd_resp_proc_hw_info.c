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
typedef  void* u32 ;
typedef  int u16 ;
struct qtnf_hw_info {void* hw_version; int /*<<< orphan*/  fw_version; void* hw_capab; int /*<<< orphan*/  total_rx_chain; int /*<<< orphan*/  total_tx_chain; int /*<<< orphan*/  mac_bitmap; void* fw_ver; int /*<<< orphan*/  max_scan_ssids; void* ql_proto_ver; int /*<<< orphan*/  num_mac; } ;
struct qtnf_bus {struct qtnf_hw_info hw_info; } ;
struct qlink_tlv_hdr {int /*<<< orphan*/ * val; int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct qlink_resp_get_hw_info {scalar_t__ info; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  plat_id; int /*<<< orphan*/  bld_tmstamp; int /*<<< orphan*/  hw_capab; int /*<<< orphan*/  total_rx_chain; int /*<<< orphan*/  total_tx_chain; int /*<<< orphan*/  ql_proto_ver; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  mac_bitmap; int /*<<< orphan*/  num_mac; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QTN_TLV_ID_BUILD_LABEL 135 
#define  QTN_TLV_ID_BUILD_NAME 134 
#define  QTN_TLV_ID_BUILD_REV 133 
#define  QTN_TLV_ID_BUILD_TYPE 132 
#define  QTN_TLV_ID_CALIBRATION_VER 131 
#define  QTN_TLV_ID_HW_ID 130 
#define  QTN_TLV_ID_MAX_SCAN_SSIDS 129 
#define  QTN_TLV_ID_UBOOT_VER 128 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,char const*,char const*,char const*,unsigned long,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
qtnf_cmd_resp_proc_hw_info(struct qtnf_bus *bus,
			   const struct qlink_resp_get_hw_info *resp,
			   size_t info_len)
{
	struct qtnf_hw_info *hwinfo = &bus->hw_info;
	const struct qlink_tlv_hdr *tlv;
	const char *bld_name = NULL;
	const char *bld_rev = NULL;
	const char *bld_type = NULL;
	const char *bld_label = NULL;
	u32 bld_tmstamp = 0;
	u32 plat_id = 0;
	const char *hw_id = NULL;
	const char *calibration_ver = NULL;
	const char *uboot_ver = NULL;
	u32 hw_ver = 0;
	u16 tlv_type;
	u16 tlv_value_len;

	hwinfo->num_mac = resp->num_mac;
	hwinfo->mac_bitmap = resp->mac_bitmap;
	hwinfo->fw_ver = le32_to_cpu(resp->fw_ver);
	hwinfo->ql_proto_ver = le16_to_cpu(resp->ql_proto_ver);
	hwinfo->total_tx_chain = resp->total_tx_chain;
	hwinfo->total_rx_chain = resp->total_rx_chain;
	hwinfo->hw_capab = le32_to_cpu(resp->hw_capab);

	bld_tmstamp = le32_to_cpu(resp->bld_tmstamp);
	plat_id = le32_to_cpu(resp->plat_id);
	hw_ver = le32_to_cpu(resp->hw_ver);

	tlv = (const struct qlink_tlv_hdr *)resp->info;

	while (info_len >= sizeof(*tlv)) {
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);

		if (tlv_value_len + sizeof(*tlv) > info_len) {
			pr_warn("malformed TLV 0x%.2X; LEN: %u\n",
				tlv_type, tlv_value_len);
			return -EINVAL;
		}

		switch (tlv_type) {
		case QTN_TLV_ID_BUILD_NAME:
			bld_name = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_BUILD_REV:
			bld_rev = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_BUILD_TYPE:
			bld_type = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_BUILD_LABEL:
			bld_label = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_HW_ID:
			hw_id = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_CALIBRATION_VER:
			calibration_ver = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_UBOOT_VER:
			uboot_ver = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_MAX_SCAN_SSIDS:
			hwinfo->max_scan_ssids = *tlv->val;
			break;
		default:
			break;
		}

		info_len -= tlv_value_len + sizeof(*tlv);
		tlv = (struct qlink_tlv_hdr *)(tlv->val + tlv_value_len);
	}

	pr_info("fw_version=%d, MACs map %#x, chains Tx=%u Rx=%u, capab=0x%x\n",
		hwinfo->fw_ver, hwinfo->mac_bitmap,
		hwinfo->total_tx_chain, hwinfo->total_rx_chain,
		hwinfo->hw_capab);

	pr_info("\nBuild name:            %s"  \
		"\nBuild revision:        %s"  \
		"\nBuild type:            %s"  \
		"\nBuild label:           %s"  \
		"\nBuild timestamp:       %lu" \
		"\nPlatform ID:           %lu" \
		"\nHardware ID:           %s"  \
		"\nCalibration version:   %s"  \
		"\nU-Boot version:        %s"  \
		"\nHardware version:      0x%08x\n",
		bld_name, bld_rev, bld_type, bld_label,
		(unsigned long)bld_tmstamp,
		(unsigned long)plat_id,
		hw_id, calibration_ver, uboot_ver, hw_ver);

	strlcpy(hwinfo->fw_version, bld_label, sizeof(hwinfo->fw_version));
	hwinfo->hw_version = hw_ver;

	return 0;
}