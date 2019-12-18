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
struct hns_mac_cb {int dummy; } ;
struct hnae_vf_cb {struct hns_mac_cb* mac_cb; } ;
struct hnae_handle {int dummy; } ;

/* Variables and functions */
 struct hnae_vf_cb* hns_ae_get_vf_cb (struct hnae_handle*) ; 

__attribute__((used)) static struct hns_mac_cb *hns_get_mac_cb(struct hnae_handle *handle)
{
	struct  hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);

	return vf_cb->mac_cb;
}