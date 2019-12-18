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
struct hns_mac_cb {scalar_t__ mac_type; } ;
struct hnae_handle {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ HNAE_PORT_SERVICE ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 int hns_mac_add_uc_addr (struct hns_mac_cb*,int /*<<< orphan*/ ,unsigned char const*) ; 

__attribute__((used)) static int hns_ae_add_uc_address(struct hnae_handle *handle,
				 const unsigned char *addr)
{
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	if (mac_cb->mac_type != HNAE_PORT_SERVICE)
		return -ENOSPC;

	return hns_mac_add_uc_addr(mac_cb, handle->vf_id, addr);
}