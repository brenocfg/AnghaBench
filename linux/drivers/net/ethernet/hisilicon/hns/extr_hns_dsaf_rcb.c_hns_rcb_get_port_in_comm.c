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
struct rcb_common_cb {int max_q_per_vf; int max_vfn; } ;

/* Variables and functions */

__attribute__((used)) static int hns_rcb_get_port_in_comm(
	struct rcb_common_cb *rcb_common, int ring_idx)
{
	return ring_idx / (rcb_common->max_q_per_vf * rcb_common->max_vfn);
}