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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  psxmitwait; int /*<<< orphan*/  psrcvpkts; int /*<<< orphan*/  psxmitpkts; int /*<<< orphan*/  psrcvdata; int /*<<< orphan*/  psxmitdata; } ;
struct TYPE_4__ {TYPE_1__ counter_cache; } ;
struct qib_pportdata {TYPE_2__ cong_stats; } ;
typedef  int __be16 ;

/* Variables and functions */
#define  IB_PMA_PORT_RCV_DATA 132 
#define  IB_PMA_PORT_RCV_PKTS 131 
#define  IB_PMA_PORT_XMIT_DATA 130 
#define  IB_PMA_PORT_XMIT_PKTS 129 
#define  IB_PMA_PORT_XMIT_WAIT 128 

__attribute__((used)) static u64 get_cache_hw_sample_counters(struct qib_pportdata *ppd,
					__be16 sel)
{
	u64 ret;

	switch (sel) {
	case IB_PMA_PORT_XMIT_DATA:
		ret = ppd->cong_stats.counter_cache.psxmitdata;
		break;
	case IB_PMA_PORT_RCV_DATA:
		ret = ppd->cong_stats.counter_cache.psrcvdata;
		break;
	case IB_PMA_PORT_XMIT_PKTS:
		ret = ppd->cong_stats.counter_cache.psxmitpkts;
		break;
	case IB_PMA_PORT_RCV_PKTS:
		ret = ppd->cong_stats.counter_cache.psrcvpkts;
		break;
	case IB_PMA_PORT_XMIT_WAIT:
		ret = ppd->cong_stats.counter_cache.psxmitwait;
		break;
	default:
		ret = 0;
	}

	return ret;
}