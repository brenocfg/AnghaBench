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
struct hns_mac_cb {int dummy; } ;
struct hnae_handle {int /*<<< orphan*/  owner_dev; int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 int hns_mac_change_vf_addr (struct hns_mac_cb*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int hns_ae_set_mac_address(struct hnae_handle *handle, void *p)
{
	int ret;
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	if (!p || !is_valid_ether_addr((const u8 *)p)) {
		dev_err(handle->owner_dev, "is not valid ether addr !\n");
		return -EADDRNOTAVAIL;
	}

	ret = hns_mac_change_vf_addr(mac_cb, handle->vf_id, p);
	if (ret != 0) {
		dev_err(handle->owner_dev,
			"set_mac_address fail, ret=%d!\n", ret);
		return ret;
	}

	return 0;
}