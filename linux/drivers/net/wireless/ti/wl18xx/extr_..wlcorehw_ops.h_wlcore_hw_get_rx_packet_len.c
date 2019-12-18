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
typedef  int /*<<< orphan*/  u32 ;
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_rx_packet_len ) (struct wl1271*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct wl1271*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
wlcore_hw_get_rx_packet_len(struct wl1271 *wl, void *rx_data, u32 data_len)
{
	if (!wl->ops->get_rx_packet_len)
		BUG_ON(1);

	return wl->ops->get_rx_packet_len(wl, rx_data, data_len);
}