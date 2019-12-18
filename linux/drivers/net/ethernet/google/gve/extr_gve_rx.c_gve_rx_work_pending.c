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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ seqno; struct gve_rx_desc* desc_ring; } ;
struct gve_rx_ring {int cnt; int mask; TYPE_1__ desc; } ;
struct gve_rx_desc {int /*<<< orphan*/  flags_seq; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ GVE_SEQNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static bool gve_rx_work_pending(struct gve_rx_ring *rx)
{
	struct gve_rx_desc *desc;
	__be16 flags_seq;
	u32 next_idx;

	next_idx = rx->cnt & rx->mask;
	desc = rx->desc.desc_ring + next_idx;

	flags_seq = desc->flags_seq;
	/* Make sure we have synchronized the seq no with the device */
	smp_rmb();

	return (GVE_SEQNO(flags_seq) == rx->desc.seqno);
}