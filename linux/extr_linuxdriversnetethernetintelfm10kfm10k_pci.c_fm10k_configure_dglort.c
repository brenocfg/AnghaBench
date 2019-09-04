#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  (* configure_dglort_map ) (struct fm10k_hw*,struct fm10k_dglort_cfg*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct fm10k_hw {TYPE_4__ mac; } ;
struct fm10k_intfc {int* rssrk; int* reta; int glort_count; TYPE_2__* l2_accel; TYPE_1__* ring_feature; scalar_t__ glort; scalar_t__ num_rx_queues; int /*<<< orphan*/  flags; struct fm10k_hw hw; } ;
struct fm10k_dglort_cfg {int inner_rss; void* shared_l; int /*<<< orphan*/  idx; void* pc_l; void* rss_l; scalar_t__ glort; void* queue_l; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  dglort ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {scalar_t__ mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_FLAG_RSS_FIELD_IPV4_UDP ; 
 int /*<<< orphan*/  FM10K_FLAG_RSS_FIELD_IPV6_UDP ; 
 int /*<<< orphan*/  FM10K_MRQC (int /*<<< orphan*/ ) ; 
 int FM10K_MRQC_IPV4 ; 
 int FM10K_MRQC_IPV6 ; 
 int FM10K_MRQC_TCP_IPV4 ; 
 int FM10K_MRQC_TCP_IPV6 ; 
 int FM10K_MRQC_UDP_IPV4 ; 
 int FM10K_MRQC_UDP_IPV6 ; 
 int /*<<< orphan*/  FM10K_RETA (int /*<<< orphan*/ ,int) ; 
 int FM10K_RETA_SIZE ; 
 int /*<<< orphan*/  FM10K_RSSRK (int /*<<< orphan*/ ,int) ; 
 int FM10K_RSSRK_SIZE ; 
 size_t RING_F_QOS ; 
 size_t RING_F_RSS ; 
 void* fls (scalar_t__) ; 
 int /*<<< orphan*/  fm10k_dglort_pf_queue ; 
 int /*<<< orphan*/  fm10k_dglort_pf_rss ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fm10k_dglort_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_dglort_cfg*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*,struct fm10k_dglort_cfg*) ; 
 int /*<<< orphan*/  stub3 (struct fm10k_hw*,struct fm10k_dglort_cfg*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_configure_dglort(struct fm10k_intfc *interface)
{
	struct fm10k_dglort_cfg dglort = { 0 };
	struct fm10k_hw *hw = &interface->hw;
	int i;
	u32 mrqc;

	/* Fill out hash function seeds */
	for (i = 0; i < FM10K_RSSRK_SIZE; i++)
		fm10k_write_reg(hw, FM10K_RSSRK(0, i), interface->rssrk[i]);

	/* Write RETA table to hardware */
	for (i = 0; i < FM10K_RETA_SIZE; i++)
		fm10k_write_reg(hw, FM10K_RETA(0, i), interface->reta[i]);

	/* Generate RSS hash based on packet types, TCP/UDP
	 * port numbers and/or IPv4/v6 src and dst addresses
	 */
	mrqc = FM10K_MRQC_IPV4 |
	       FM10K_MRQC_TCP_IPV4 |
	       FM10K_MRQC_IPV6 |
	       FM10K_MRQC_TCP_IPV6;

	if (test_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP, interface->flags))
		mrqc |= FM10K_MRQC_UDP_IPV4;
	if (test_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP, interface->flags))
		mrqc |= FM10K_MRQC_UDP_IPV6;

	fm10k_write_reg(hw, FM10K_MRQC(0), mrqc);

	/* configure default DGLORT mapping for RSS/DCB */
	dglort.inner_rss = 1;
	dglort.rss_l = fls(interface->ring_feature[RING_F_RSS].mask);
	dglort.pc_l = fls(interface->ring_feature[RING_F_QOS].mask);
	hw->mac.ops.configure_dglort_map(hw, &dglort);

	/* assign GLORT per queue for queue mapped testing */
	if (interface->glort_count > 64) {
		memset(&dglort, 0, sizeof(dglort));
		dglort.inner_rss = 1;
		dglort.glort = interface->glort + 64;
		dglort.idx = fm10k_dglort_pf_queue;
		dglort.queue_l = fls(interface->num_rx_queues - 1);
		hw->mac.ops.configure_dglort_map(hw, &dglort);
	}

	/* assign glort value for RSS/DCB specific to this interface */
	memset(&dglort, 0, sizeof(dglort));
	dglort.inner_rss = 1;
	dglort.glort = interface->glort;
	dglort.rss_l = fls(interface->ring_feature[RING_F_RSS].mask);
	dglort.pc_l = fls(interface->ring_feature[RING_F_QOS].mask);
	/* configure DGLORT mapping for RSS/DCB */
	dglort.idx = fm10k_dglort_pf_rss;
	if (interface->l2_accel)
		dglort.shared_l = fls(interface->l2_accel->size);
	hw->mac.ops.configure_dglort_map(hw, &dglort);
}