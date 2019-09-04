#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tp_tcp_stats {int /*<<< orphan*/  tcp_out_rsts; int /*<<< orphan*/  tcp_retrans_segs; int /*<<< orphan*/  tcp_out_segs; int /*<<< orphan*/  tcp_in_segs; } ;
struct rdma_hw_stats {int num_counters; int /*<<< orphan*/ * value; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {TYPE_1__ lldi; } ;
struct c4iw_dev {TYPE_2__ rdev; } ;

/* Variables and functions */
 size_t IP4INSEGS ; 
 size_t IP4OUTRSTS ; 
 size_t IP4OUTSEGS ; 
 size_t IP4RETRANSSEGS ; 
 size_t IP6INSEGS ; 
 size_t IP6OUTRSTS ; 
 size_t IP6OUTSEGS ; 
 size_t IP6RETRANSSEGS ; 
 int /*<<< orphan*/  cxgb4_get_tcp_stats (int /*<<< orphan*/ ,struct tp_tcp_stats*,struct tp_tcp_stats*) ; 
 struct c4iw_dev* to_c4iw_dev (struct ib_device*) ; 

__attribute__((used)) static int c4iw_get_mib(struct ib_device *ibdev,
			struct rdma_hw_stats *stats,
			u8 port, int index)
{
	struct tp_tcp_stats v4, v6;
	struct c4iw_dev *c4iw_dev = to_c4iw_dev(ibdev);

	cxgb4_get_tcp_stats(c4iw_dev->rdev.lldi.pdev, &v4, &v6);
	stats->value[IP4INSEGS] = v4.tcp_in_segs;
	stats->value[IP4OUTSEGS] = v4.tcp_out_segs;
	stats->value[IP4RETRANSSEGS] = v4.tcp_retrans_segs;
	stats->value[IP4OUTRSTS] = v4.tcp_out_rsts;
	stats->value[IP6INSEGS] = v6.tcp_in_segs;
	stats->value[IP6OUTSEGS] = v6.tcp_out_segs;
	stats->value[IP6RETRANSSEGS] = v6.tcp_retrans_segs;
	stats->value[IP6OUTRSTS] = v6.tcp_out_rsts;

	return stats->num_counters;
}