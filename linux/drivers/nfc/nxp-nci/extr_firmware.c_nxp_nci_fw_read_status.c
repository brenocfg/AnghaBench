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
typedef  int u8 ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EALREADY ; 
 int EHWPOISON ; 
 int EINVAL ; 
 int EIO ; 
 int EKEYREJECTED ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENOKEY ; 
 int EPROTO ; 
#define  NXP_NCI_FW_RESULT_ABORTED_CMD 141 
#define  NXP_NCI_FW_RESULT_ADDR_RANGE_OFL_ERROR 140 
#define  NXP_NCI_FW_RESULT_BUFFER_OFL_ERROR 139 
#define  NXP_NCI_FW_RESULT_FIRMWARE_VERSION_ERROR 138 
#define  NXP_NCI_FW_RESULT_INVALID_ADDR 137 
#define  NXP_NCI_FW_RESULT_MEM_BSY 136 
#define  NXP_NCI_FW_RESULT_OK 135 
#define  NXP_NCI_FW_RESULT_PH_STATUS_FIRST_CHUNK 134 
#define  NXP_NCI_FW_RESULT_PH_STATUS_INTERNAL_ERROR_5 133 
#define  NXP_NCI_FW_RESULT_PH_STATUS_NEXT_CHUNK 132 
#define  NXP_NCI_FW_RESULT_PROTOCOL_ERROR 131 
#define  NXP_NCI_FW_RESULT_SFWU_DEGRADED 130 
#define  NXP_NCI_FW_RESULT_SIGNATURE_ERROR 129 
#define  NXP_NCI_FW_RESULT_UNKNOWN_CMD 128 

__attribute__((used)) static int nxp_nci_fw_read_status(u8 stat)
{
	switch (stat) {
	case NXP_NCI_FW_RESULT_OK:
		return 0;
	case NXP_NCI_FW_RESULT_INVALID_ADDR:
		return -EINVAL;
	case NXP_NCI_FW_RESULT_UNKNOWN_CMD:
		return -EINVAL;
	case NXP_NCI_FW_RESULT_ABORTED_CMD:
		return -EMSGSIZE;
	case NXP_NCI_FW_RESULT_ADDR_RANGE_OFL_ERROR:
		return -EADDRNOTAVAIL;
	case NXP_NCI_FW_RESULT_BUFFER_OFL_ERROR:
		return -ENOBUFS;
	case NXP_NCI_FW_RESULT_MEM_BSY:
		return -ENOKEY;
	case NXP_NCI_FW_RESULT_SIGNATURE_ERROR:
		return -EKEYREJECTED;
	case NXP_NCI_FW_RESULT_FIRMWARE_VERSION_ERROR:
		return -EALREADY;
	case NXP_NCI_FW_RESULT_PROTOCOL_ERROR:
		return -EPROTO;
	case NXP_NCI_FW_RESULT_SFWU_DEGRADED:
		return -EHWPOISON;
	case NXP_NCI_FW_RESULT_PH_STATUS_FIRST_CHUNK:
		return 0;
	case NXP_NCI_FW_RESULT_PH_STATUS_NEXT_CHUNK:
		return 0;
	case NXP_NCI_FW_RESULT_PH_STATUS_INTERNAL_ERROR_5:
		return -EINVAL;
	default:
		return -EIO;
	}
}