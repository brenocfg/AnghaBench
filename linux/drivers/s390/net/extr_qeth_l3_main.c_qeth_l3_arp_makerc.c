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

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  IPA_RC_SUCCESS 132 
#define  QETH_IPA_ARP_RC_NOTSUPP 131 
#define  QETH_IPA_ARP_RC_OUT_OF_RANGE 130 
#define  QETH_IPA_ARP_RC_Q_NOTSUPP 129 
#define  QETH_IPA_ARP_RC_Q_NO_DATA 128 

__attribute__((used)) static int qeth_l3_arp_makerc(u16 rc)
{
	switch (rc) {
	case IPA_RC_SUCCESS:
		return 0;
	case QETH_IPA_ARP_RC_NOTSUPP:
	case QETH_IPA_ARP_RC_Q_NOTSUPP:
		return -EOPNOTSUPP;
	case QETH_IPA_ARP_RC_OUT_OF_RANGE:
		return -EINVAL;
	case QETH_IPA_ARP_RC_Q_NO_DATA:
		return -ENOENT;
	default:
		return -EIO;
	}
}