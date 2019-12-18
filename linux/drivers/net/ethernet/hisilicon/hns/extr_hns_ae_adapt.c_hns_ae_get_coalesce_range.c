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
typedef  int u32 ;
struct hnae_handle {scalar_t__ port_type; int /*<<< orphan*/  dev; } ;
struct dsaf_device {int desc_num; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 scalar_t__ HNAE_PORT_DEBUG ; 
 int HNS_RCB_RX_FRAMES_HIGH ; 
 int HNS_RCB_RX_FRAMES_LOW ; 
 int HNS_RCB_RX_USECS_HIGH ; 
 int HNS_RCB_RX_USECS_LOW ; 
 int HNS_RCB_TX_FRAMES_HIGH ; 
 int HNS_RCB_TX_FRAMES_LOW ; 
 int HNS_RCB_TX_USECS_HIGH ; 
 int HNS_RCB_TX_USECS_LOW ; 
 int /*<<< orphan*/  assert (struct hnae_handle*) ; 
 struct dsaf_device* hns_ae_get_dsaf_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_ae_get_coalesce_range(struct hnae_handle *handle,
				      u32 *tx_frames_low, u32 *rx_frames_low,
				      u32 *tx_frames_high, u32 *rx_frames_high,
				      u32 *tx_usecs_low, u32 *rx_usecs_low,
				      u32 *tx_usecs_high, u32 *rx_usecs_high)
{
	struct dsaf_device *dsaf_dev;

	assert(handle);

	dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);

	*tx_frames_low  = HNS_RCB_TX_FRAMES_LOW;
	*rx_frames_low  = HNS_RCB_RX_FRAMES_LOW;

	if (AE_IS_VER1(dsaf_dev->dsaf_ver) ||
	    handle->port_type == HNAE_PORT_DEBUG)
		*tx_frames_high =
			(dsaf_dev->desc_num - 1 > HNS_RCB_TX_FRAMES_HIGH) ?
			HNS_RCB_TX_FRAMES_HIGH : dsaf_dev->desc_num - 1;
	else
		*tx_frames_high = 1;

	*rx_frames_high = (dsaf_dev->desc_num - 1 > HNS_RCB_RX_FRAMES_HIGH) ?
		HNS_RCB_RX_FRAMES_HIGH : dsaf_dev->desc_num - 1;
	*tx_usecs_low   = HNS_RCB_TX_USECS_LOW;
	*rx_usecs_low   = HNS_RCB_RX_USECS_LOW;
	*tx_usecs_high  = HNS_RCB_TX_USECS_HIGH;
	*rx_usecs_high  = HNS_RCB_RX_USECS_HIGH;
}