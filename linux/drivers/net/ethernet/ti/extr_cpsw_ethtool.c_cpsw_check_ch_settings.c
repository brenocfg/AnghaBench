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
struct ethtool_channels {scalar_t__ rx_count; scalar_t__ tx_count; scalar_t__ combined_count; } ;
struct TYPE_2__ {scalar_t__ channels; } ;
struct cpsw_common {TYPE_1__ data; int /*<<< orphan*/  dev; scalar_t__ quirk_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cpsw_check_ch_settings(struct cpsw_common *cpsw,
				  struct ethtool_channels *ch)
{
	if (cpsw->quirk_irq) {
		dev_err(cpsw->dev, "Maximum one tx/rx queue is allowed");
		return -EOPNOTSUPP;
	}

	if (ch->combined_count)
		return -EINVAL;

	/* verify we have at least one channel in each direction */
	if (!ch->rx_count || !ch->tx_count)
		return -EINVAL;

	if (ch->rx_count > cpsw->data.channels ||
	    ch->tx_count > cpsw->data.channels)
		return -EINVAL;

	return 0;
}