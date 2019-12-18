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
struct TYPE_2__ {int /*<<< orphan*/  flow; int /*<<< orphan*/  num_hw_channels; int /*<<< orphan*/  mode; } ;
struct hsi_client {TYPE_1__ rx_cfg; } ;
struct hsc_rx_config {int /*<<< orphan*/  flow; int /*<<< orphan*/  channels; int /*<<< orphan*/  mode; } ;

/* Variables and functions */

__attribute__((used)) static inline void hsc_rx_get(struct hsi_client *cl, struct hsc_rx_config *rxc)
{
	rxc->mode = cl->rx_cfg.mode;
	rxc->channels = cl->rx_cfg.num_hw_channels;
	rxc->flow = cl->rx_cfg.flow;
}