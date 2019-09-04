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
struct ring_pair_cb {int dummy; } ;
struct rcb_common_cb {int max_q_per_vf; int max_vfn; struct ring_pair_cb* ring_pair_cb; } ;
struct dsaf_device {struct rcb_common_cb** rcb_common; } ;

/* Variables and functions */

__attribute__((used)) static struct ring_pair_cb *hns_ae_get_base_ring_pair(
	struct dsaf_device *dsaf_dev, int port)
{
	struct rcb_common_cb *rcb_comm = dsaf_dev->rcb_common[0];
	int q_num = rcb_comm->max_q_per_vf;
	int vf_num = rcb_comm->max_vfn;

	return &rcb_comm->ring_pair_cb[port * q_num * vf_num];
}