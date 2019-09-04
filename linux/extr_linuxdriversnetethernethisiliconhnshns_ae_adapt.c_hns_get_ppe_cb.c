#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ppe_common_cb {struct hns_ppe_cb* ppe_cb; } ;
struct hns_ppe_cb {int dummy; } ;
struct hnae_vf_cb {int port_index; TYPE_1__* dsaf_dev; } ;
struct hnae_handle {int dummy; } ;
struct TYPE_2__ {struct ppe_common_cb** ppe_common; } ;

/* Variables and functions */
 struct hnae_vf_cb* hns_ae_get_vf_cb (struct hnae_handle*) ; 

__attribute__((used)) static struct hns_ppe_cb *hns_get_ppe_cb(struct hnae_handle *handle)
{
	int ppe_index;
	struct ppe_common_cb *ppe_comm;
	struct  hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);

	ppe_comm = vf_cb->dsaf_dev->ppe_common[0];
	ppe_index = vf_cb->port_index;

	return &ppe_comm->ppe_cb[ppe_index];
}