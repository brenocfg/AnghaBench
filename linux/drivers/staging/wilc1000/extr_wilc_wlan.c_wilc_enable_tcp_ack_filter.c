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
struct TYPE_2__ {int enabled; } ;
struct wilc_vif {TYPE_1__ ack_filter; } ;

/* Variables and functions */

void wilc_enable_tcp_ack_filter(struct wilc_vif *vif, bool value)
{
	vif->ack_filter.enabled = value;
}