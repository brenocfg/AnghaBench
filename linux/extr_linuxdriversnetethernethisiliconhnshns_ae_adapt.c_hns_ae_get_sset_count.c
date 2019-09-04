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
typedef  int u32 ;
struct hns_mac_cb {scalar_t__ mac_type; } ;
struct hnae_handle {int q_num; int /*<<< orphan*/  dev; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HNAE_PORT_SERVICE ; 
 int /*<<< orphan*/  assert (struct hnae_handle*) ; 
 struct dsaf_device* hns_ae_get_dsaf_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ hns_dsaf_get_sset_count (struct dsaf_device*,int) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 scalar_t__ hns_mac_get_sset_count (struct hns_mac_cb*,int) ; 
 scalar_t__ hns_ppe_get_sset_count (int) ; 
 int hns_rcb_get_ring_sset_count (int) ; 

__attribute__((used)) static int hns_ae_get_sset_count(struct hnae_handle *handle, int stringset)
{
	u32 sset_count = 0;
	struct hns_mac_cb *mac_cb;
	struct dsaf_device *dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);

	assert(handle);

	mac_cb = hns_get_mac_cb(handle);

	sset_count += hns_rcb_get_ring_sset_count(stringset) * handle->q_num;
	sset_count += hns_ppe_get_sset_count(stringset);
	sset_count += hns_mac_get_sset_count(mac_cb, stringset);

	if (mac_cb->mac_type == HNAE_PORT_SERVICE)
		sset_count += hns_dsaf_get_sset_count(dsaf_dev, stringset);

	return sset_count;
}