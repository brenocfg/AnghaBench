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
typedef  int /*<<< orphan*/  u32 ;
struct ena_com_dev {int /*<<< orphan*/  intr_moder_tx_interval; int /*<<< orphan*/  intr_delay_resolution; } ;

/* Variables and functions */
 int ena_com_update_nonadaptive_moderation_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ena_com_update_nonadaptive_moderation_interval_tx(struct ena_com_dev *ena_dev,
						      u32 tx_coalesce_usecs)
{
	return ena_com_update_nonadaptive_moderation_interval(tx_coalesce_usecs,
							      ena_dev->intr_delay_resolution,
							      &ena_dev->intr_moder_tx_interval);
}