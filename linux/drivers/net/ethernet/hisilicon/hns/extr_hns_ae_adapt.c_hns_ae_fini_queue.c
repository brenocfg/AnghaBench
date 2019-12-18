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
struct hnae_vf_cb {TYPE_1__* mac_cb; } ;
struct hnae_queue {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {scalar_t__ mac_type; } ;

/* Variables and functions */
 scalar_t__ HNAE_PORT_SERVICE ; 
 struct hnae_vf_cb* hns_ae_get_vf_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_rcb_reset_ring_hw (struct hnae_queue*) ; 

__attribute__((used)) static void hns_ae_fini_queue(struct hnae_queue *q)
{
	struct hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(q->handle);

	if (vf_cb->mac_cb->mac_type == HNAE_PORT_SERVICE)
		hns_rcb_reset_ring_hw(q);
}