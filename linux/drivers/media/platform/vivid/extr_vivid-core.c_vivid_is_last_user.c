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
struct vivid_dev {int /*<<< orphan*/  radio_tx_dev; int /*<<< orphan*/  radio_rx_dev; int /*<<< orphan*/  sdr_cap_dev; int /*<<< orphan*/  vbi_out_dev; int /*<<< orphan*/  vbi_cap_dev; int /*<<< orphan*/  vid_out_dev; int /*<<< orphan*/  vid_cap_dev; } ;

/* Variables and functions */
 unsigned int vivid_is_in_use (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vivid_is_last_user(struct vivid_dev *dev)
{
	unsigned uses = vivid_is_in_use(&dev->vid_cap_dev) +
			vivid_is_in_use(&dev->vid_out_dev) +
			vivid_is_in_use(&dev->vbi_cap_dev) +
			vivid_is_in_use(&dev->vbi_out_dev) +
			vivid_is_in_use(&dev->sdr_cap_dev) +
			vivid_is_in_use(&dev->radio_rx_dev) +
			vivid_is_in_use(&dev->radio_tx_dev);

	return uses == 1;
}