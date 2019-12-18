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
struct wil_rx_status_compressed {int /*<<< orphan*/  buff_id; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */

__attribute__((used)) static inline __le16 wil_rx_status_get_buff_id(void *msg)
{
	return ((struct wil_rx_status_compressed *)msg)->buff_id;
}