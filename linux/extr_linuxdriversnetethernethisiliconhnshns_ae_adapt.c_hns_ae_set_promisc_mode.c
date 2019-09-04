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
typedef  int /*<<< orphan*/  u32 ;
struct hns_mac_cb {int dummy; } ;
struct hnae_handle {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_ae_get_dsaf_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_set_promisc_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_mac_set_promisc (struct hns_mac_cb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_ae_set_promisc_mode(struct hnae_handle *handle, u32 en)
{
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	hns_dsaf_set_promisc_mode(hns_ae_get_dsaf_dev(handle->dev), en);
	hns_mac_set_promisc(mac_cb, (u8)!!en);
}