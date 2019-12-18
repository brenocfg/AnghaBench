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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  RNDIS_OID_802_11_BSSID ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 
 int rndis_query_oid (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int get_bssid(struct usbnet *usbdev, u8 bssid[ETH_ALEN])
{
	int ret, len;

	len = ETH_ALEN;
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_BSSID,
			      bssid, &len);

	if (ret != 0)
		eth_zero_addr(bssid);

	return ret;
}