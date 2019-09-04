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
typedef  int /*<<< orphan*/  u32 ;
struct hnae_ring {scalar_t__ coal_last_rx_bytes; TYPE_2__* q; } ;
struct TYPE_4__ {TYPE_1__* handle; } ;
struct TYPE_3__ {int coal_adapt_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_COAL_BDNUM ; 
 scalar_t__ HNS_LOWEST_LATENCY_RATE ; 

__attribute__((used)) static u32 hns_coal_rx_bdnum(struct hnae_ring *ring)
{
	bool coal_enable = ring->q->handle->coal_adapt_en;

	if (coal_enable &&
	    ring->coal_last_rx_bytes > HNS_LOWEST_LATENCY_RATE)
		return HNS_COAL_BDNUM;
	else
		return 0;
}