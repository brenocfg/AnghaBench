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
typedef  int umode_t ;

/* Variables and functions */
#define  ISCSI_BOOT_ETH_FLAGS 130 
#define  ISCSI_BOOT_ETH_INDEX 129 
#define  ISCSI_BOOT_ETH_MAC 128 
 int S_IRUGO ; 

__attribute__((used)) static umode_t qla4xxx_eth_get_attr_visibility(void *data, int type)
{
	int rc;

	switch (type) {
	case ISCSI_BOOT_ETH_FLAGS:
	case ISCSI_BOOT_ETH_MAC:
	case ISCSI_BOOT_ETH_INDEX:
		rc = S_IRUGO;
		break;
	default:
		rc = 0;
		break;
	}
	return rc;
}