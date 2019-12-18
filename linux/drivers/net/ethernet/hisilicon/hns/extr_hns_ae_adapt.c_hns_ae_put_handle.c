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
struct hnae_vf_cb {int dummy; } ;
struct hnae_handle {int q_num; int /*<<< orphan*/ * qs; } ;
struct TYPE_2__ {scalar_t__ used_by_vf; } ;

/* Variables and functions */
 TYPE_1__* hns_ae_get_ring_pair (int /*<<< orphan*/ ) ; 
 struct hnae_vf_cb* hns_ae_get_vf_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  kfree (struct hnae_vf_cb*) ; 

__attribute__((used)) static void hns_ae_put_handle(struct hnae_handle *handle)
{
	struct hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	int i;

	for (i = 0; i < handle->q_num; i++)
		hns_ae_get_ring_pair(handle->qs[i])->used_by_vf = 0;

	kfree(vf_cb);
}