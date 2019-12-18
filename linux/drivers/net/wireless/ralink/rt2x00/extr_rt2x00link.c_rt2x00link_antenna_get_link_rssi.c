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
struct TYPE_3__ {scalar_t__ rx_success; } ;
struct link_ant {int /*<<< orphan*/  rssi_ant; } ;
struct TYPE_4__ {TYPE_1__ qual; struct link_ant ant; } ;
struct rt2x00_dev {TYPE_2__ link; } ;

/* Variables and functions */
 int DEFAULT_RSSI ; 
 int rt2x00link_get_avg_rssi (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt2x00link_antenna_get_link_rssi(struct rt2x00_dev *rt2x00dev)
{
	struct link_ant *ant = &rt2x00dev->link.ant;

	if (rt2x00dev->link.qual.rx_success)
		return rt2x00link_get_avg_rssi(&ant->rssi_ant);

	return DEFAULT_RSSI;
}