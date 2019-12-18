#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct TYPE_17__ {int ctrl_flags; } ;
struct TYPE_15__ {char* byte; } ;
struct TYPE_14__ {char* byte; } ;
struct TYPE_16__ {TYPE_2__ chap_password; TYPE_1__ chap_name; } ;
struct nvm_iscsi_block {TYPE_11__* target; TYPE_4__ generic; TYPE_3__ initiator; int /*<<< orphan*/  id; } ;
typedef  int ssize_t ;
typedef  enum qedi_nvm_tgts { ____Placeholder_qedi_nvm_tgts } qedi_nvm_tgts ;
struct TYPE_22__ {int /*<<< orphan*/  byte; } ;
struct TYPE_21__ {int /*<<< orphan*/  byte; } ;
struct TYPE_20__ {char* byte; } ;
struct TYPE_19__ {char* byte; } ;
struct TYPE_18__ {char* byte; } ;
struct TYPE_12__ {int* value; } ;
struct TYPE_13__ {int ctrl_flags; TYPE_10__ lun; int /*<<< orphan*/  generic_cont0; TYPE_9__ ipv4_addr; TYPE_8__ ipv6_addr; TYPE_7__ target_name; TYPE_6__ chap_password; TYPE_5__ chap_name; } ;

/* Variables and functions */
 int GET_FIELD2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IPV4_LEN ; 
 int IPV6_LEN ; 
#define  ISCSI_BOOT_TGT_CHAP_NAME 137 
#define  ISCSI_BOOT_TGT_CHAP_SECRET 136 
#define  ISCSI_BOOT_TGT_FLAGS 135 
#define  ISCSI_BOOT_TGT_IP_ADDR 134 
#define  ISCSI_BOOT_TGT_LUN 133 
#define  ISCSI_BOOT_TGT_NAME 132 
#define  ISCSI_BOOT_TGT_NIC_ASSOC 131 
#define  ISCSI_BOOT_TGT_PORT 130 
#define  ISCSI_BOOT_TGT_REV_CHAP_NAME 129 
#define  ISCSI_BOOT_TGT_REV_CHAP_SECRET 128 
 int /*<<< orphan*/  NVM_ISCSI_CFG_BLK_MAPPED_PF_ID ; 
 char* NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN ; 
 int NVM_ISCSI_CFG_GEN_CHAP_ENABLED ; 
 int NVM_ISCSI_CFG_GEN_CHAP_MUTUAL_ENABLED ; 
 int NVM_ISCSI_CFG_GEN_IPV6_ENABLED ; 
 char* NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN ; 
 int NVM_ISCSI_CFG_TARGET_ENABLED ; 
 int /*<<< orphan*/  NVM_ISCSI_CFG_TARGET_TCP_PORT ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDI_LOG_EVT ; 
 int /*<<< orphan*/  SYSFS_FLAG_FW_SEL_BOOT ; 
 struct nvm_iscsi_block* qedi_get_nvram_block (struct qedi_ctx*) ; 
 int snprintf (char*,int,char*,...) ; 
 int sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static ssize_t
qedi_show_boot_tgt_info(struct qedi_ctx *qedi, int type,
			char *buf, enum qedi_nvm_tgts idx)
{
	int rc = 1;
	u32 ctrl_flags, ipv6_en, chap_en, mchap_en, ip_len;
	struct nvm_iscsi_block *block;
	char *chap_name, *chap_secret;
	char *mchap_name, *mchap_secret;

	block = qedi_get_nvram_block(qedi);
	if (!block)
		goto exit_show_tgt_info;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_EVT,
		  "Port:%d, tgt_idx:%d\n",
		  GET_FIELD2(block->id, NVM_ISCSI_CFG_BLK_MAPPED_PF_ID), idx);

	ctrl_flags = block->target[idx].ctrl_flags &
		     NVM_ISCSI_CFG_TARGET_ENABLED;

	if (!ctrl_flags) {
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_EVT,
			  "Target disabled\n");
		goto exit_show_tgt_info;
	}

	ipv6_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_IPV6_ENABLED;
	ip_len = ipv6_en ? IPV6_LEN : IPV4_LEN;
	chap_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_CHAP_ENABLED;
	chap_name = chap_en ? block->initiator.chap_name.byte : NULL;
	chap_secret = chap_en ? block->initiator.chap_password.byte : NULL;

	mchap_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_CHAP_MUTUAL_ENABLED;
	mchap_name = mchap_en ? block->target[idx].chap_name.byte : NULL;
	mchap_secret = mchap_en ? block->target[idx].chap_password.byte : NULL;

	switch (type) {
	case ISCSI_BOOT_TGT_NAME:
		rc = sprintf(buf, "%.*s\n", NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN,
			     block->target[idx].target_name.byte);
		break;
	case ISCSI_BOOT_TGT_IP_ADDR:
		if (ipv6_en)
			rc = snprintf(buf, ip_len, "%pI6\n",
				      block->target[idx].ipv6_addr.byte);
		else
			rc = snprintf(buf, ip_len, "%pI4\n",
				      block->target[idx].ipv4_addr.byte);
		break;
	case ISCSI_BOOT_TGT_PORT:
		rc = snprintf(buf, 12, "%d\n",
			      GET_FIELD2(block->target[idx].generic_cont0,
					 NVM_ISCSI_CFG_TARGET_TCP_PORT));
		break;
	case ISCSI_BOOT_TGT_LUN:
		rc = snprintf(buf, 22, "%.*d\n",
			      block->target[idx].lun.value[1],
			      block->target[idx].lun.value[0]);
		break;
	case ISCSI_BOOT_TGT_CHAP_NAME:
		rc = sprintf(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN,
			     chap_name);
		break;
	case ISCSI_BOOT_TGT_CHAP_SECRET:
		rc = sprintf(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN,
			     chap_secret);
		break;
	case ISCSI_BOOT_TGT_REV_CHAP_NAME:
		rc = sprintf(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN,
			     mchap_name);
		break;
	case ISCSI_BOOT_TGT_REV_CHAP_SECRET:
		rc = sprintf(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN,
			     mchap_secret);
		break;
	case ISCSI_BOOT_TGT_FLAGS:
		rc = snprintf(buf, 3, "%hhd\n", SYSFS_FLAG_FW_SEL_BOOT);
		break;
	case ISCSI_BOOT_TGT_NIC_ASSOC:
		rc = snprintf(buf, 3, "0\n");
		break;
	default:
		rc = 0;
		break;
	}

exit_show_tgt_info:
	return rc;
}