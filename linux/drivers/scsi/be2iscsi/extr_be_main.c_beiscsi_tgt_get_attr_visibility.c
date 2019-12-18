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
typedef  int /*<<< orphan*/  umode_t ;

/* Variables and functions */
#define  ISCSI_BOOT_TGT_CHAP_NAME 136 
#define  ISCSI_BOOT_TGT_CHAP_SECRET 135 
#define  ISCSI_BOOT_TGT_FLAGS 134 
#define  ISCSI_BOOT_TGT_IP_ADDR 133 
#define  ISCSI_BOOT_TGT_NAME 132 
#define  ISCSI_BOOT_TGT_NIC_ASSOC 131 
#define  ISCSI_BOOT_TGT_PORT 130 
#define  ISCSI_BOOT_TGT_REV_CHAP_NAME 129 
#define  ISCSI_BOOT_TGT_REV_CHAP_SECRET 128 
 int /*<<< orphan*/  S_IRUGO ; 

__attribute__((used)) static umode_t beiscsi_tgt_get_attr_visibility(void *data, int type)
{
	umode_t rc = 0;

	switch (type) {
	case ISCSI_BOOT_TGT_NAME:
	case ISCSI_BOOT_TGT_IP_ADDR:
	case ISCSI_BOOT_TGT_PORT:
	case ISCSI_BOOT_TGT_CHAP_NAME:
	case ISCSI_BOOT_TGT_CHAP_SECRET:
	case ISCSI_BOOT_TGT_REV_CHAP_NAME:
	case ISCSI_BOOT_TGT_REV_CHAP_SECRET:
	case ISCSI_BOOT_TGT_NIC_ASSOC:
	case ISCSI_BOOT_TGT_FLAGS:
		rc = S_IRUGO;
		break;
	}
	return rc;
}