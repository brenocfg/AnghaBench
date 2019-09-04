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
struct TYPE_4__ {scalar_t__ size; scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ data; } ;
struct tegra_bpmp_message {TYPE_2__ rx; TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ MSG_DATA_MIN_SZ ; 

__attribute__((used)) static bool tegra_bpmp_message_valid(const struct tegra_bpmp_message *msg)
{
	return (msg->tx.size <= MSG_DATA_MIN_SZ) &&
	       (msg->rx.size <= MSG_DATA_MIN_SZ) &&
	       (msg->tx.size == 0 || msg->tx.data) &&
	       (msg->rx.size == 0 || msg->rx.data);
}