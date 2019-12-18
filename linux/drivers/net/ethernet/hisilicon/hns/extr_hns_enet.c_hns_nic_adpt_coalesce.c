#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct hns_nic_ring_data {scalar_t__ queue_index; struct hnae_ring* ring; } ;
struct hnae_ring {scalar_t__ coal_param; scalar_t__ coal_rx_rate; TYPE_1__* q; } ;
struct hnae_handle {scalar_t__ coal_param; scalar_t__ coal_ring_idx; void* coal_last_jiffies; TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_coalesce_frames ) (struct hnae_handle*,int,scalar_t__) ;int /*<<< orphan*/  (* set_coalesce_usecs ) (struct hnae_handle*,scalar_t__) ;} ;
struct TYPE_4__ {struct hnae_handle* handle; } ;

/* Variables and functions */
 scalar_t__ HNAE_BULK_LATENCY_COAL_PARAM ; 
 scalar_t__ HNAE_LOWEST_LATENCY_COAL_PARAM ; 
 scalar_t__ HNAE_LOW_LATENCY_COAL_PARAM ; 
 scalar_t__ HNS_LOWEST_LATENCY_RATE ; 
 scalar_t__ HNS_LOW_LATENCY_RATE ; 
 int HZ ; 
 void* jiffies ; 
 scalar_t__ smooth_alg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct hnae_handle*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct hnae_handle*,int,scalar_t__) ; 
 scalar_t__ time_after (void*,void*) ; 

__attribute__((used)) static void hns_nic_adpt_coalesce(struct hns_nic_ring_data *ring_data)
{
	struct hnae_ring *ring = ring_data->ring;
	struct hnae_handle *handle = ring->q->handle;
	u32 new_coal_param, old_coal_param = ring->coal_param;

	if (ring->coal_rx_rate < HNS_LOWEST_LATENCY_RATE)
		new_coal_param = HNAE_LOWEST_LATENCY_COAL_PARAM;
	else if (ring->coal_rx_rate < HNS_LOW_LATENCY_RATE)
		new_coal_param = HNAE_LOW_LATENCY_COAL_PARAM;
	else
		new_coal_param = HNAE_BULK_LATENCY_COAL_PARAM;

	if (new_coal_param == old_coal_param &&
	    new_coal_param == handle->coal_param)
		return;

	new_coal_param = smooth_alg(new_coal_param, old_coal_param);
	ring->coal_param = new_coal_param;

	/**
	 * Because all ring in one port has one coalesce param, when one ring
	 * calculate its own coalesce param, it cannot write to hardware at
	 * once. There are three conditions as follows:
	 *       1. current ring's coalesce param is larger than the hardware.
	 *       2. or ring which adapt last time can change again.
	 *       3. timeout.
	 */
	if (new_coal_param == handle->coal_param) {
		handle->coal_last_jiffies = jiffies;
		handle->coal_ring_idx = ring_data->queue_index;
	} else if (new_coal_param > handle->coal_param ||
		   handle->coal_ring_idx == ring_data->queue_index ||
		   time_after(jiffies, handle->coal_last_jiffies + (HZ >> 4))) {
		handle->dev->ops->set_coalesce_usecs(handle,
					new_coal_param);
		handle->dev->ops->set_coalesce_frames(handle,
					1, new_coal_param);
		handle->coal_param = new_coal_param;
		handle->coal_ring_idx = ring_data->queue_index;
		handle->coal_last_jiffies = jiffies;
	}
}