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
 int RTLLIB_1ADDR_LEN ; 
 int RTLLIB_2ADDR_LEN ; 
 int RTLLIB_3ADDR_LEN ; 
 int RTLLIB_4ADDR_LEN ; 
 int RTLLIB_FCTL_FROMDS ; 
 int RTLLIB_FCTL_TODS ; 
#define  RTLLIB_FTYPE_CTL 131 
#define  RTLLIB_FTYPE_DATA 130 
 int /*<<< orphan*/  RTLLIB_QOS_HAS_SEQ (int) ; 
#define  RTLLIB_STYPE_ACK 129 
#define  RTLLIB_STYPE_CTS 128 
 int /*<<< orphan*/  WLAN_FC_GET_STYPE (int) ; 
 int WLAN_FC_GET_TYPE (int) ; 

__attribute__((used)) static inline int rtllib_get_hdrlen(u16 fc)
{
	int hdrlen = RTLLIB_3ADDR_LEN;

	switch (WLAN_FC_GET_TYPE(fc)) {
	case RTLLIB_FTYPE_DATA:
		if ((fc & RTLLIB_FCTL_FROMDS) && (fc & RTLLIB_FCTL_TODS))
			hdrlen = RTLLIB_4ADDR_LEN; /* Addr4 */
		if (RTLLIB_QOS_HAS_SEQ(fc))
			hdrlen += 2; /* QOS ctrl*/
		break;
	case RTLLIB_FTYPE_CTL:
		switch (WLAN_FC_GET_STYPE(fc)) {
		case RTLLIB_STYPE_CTS:
		case RTLLIB_STYPE_ACK:
			hdrlen = RTLLIB_1ADDR_LEN;
			break;
		default:
			hdrlen = RTLLIB_2ADDR_LEN;
			break;
		}
		break;
	}

	return hdrlen;
}