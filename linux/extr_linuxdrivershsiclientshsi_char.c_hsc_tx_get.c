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
struct TYPE_2__ {int /*<<< orphan*/  arb_mode; int /*<<< orphan*/  speed; int /*<<< orphan*/  num_hw_channels; int /*<<< orphan*/  mode; } ;
struct hsi_client {TYPE_1__ tx_cfg; } ;
struct hsc_tx_config {int /*<<< orphan*/  arb_mode; int /*<<< orphan*/  speed; int /*<<< orphan*/  channels; int /*<<< orphan*/  mode; } ;

/* Variables and functions */

__attribute__((used)) static inline void hsc_tx_get(struct hsi_client *cl, struct hsc_tx_config *txc)
{
	txc->mode = cl->tx_cfg.mode;
	txc->channels = cl->tx_cfg.num_hw_channels;
	txc->speed = cl->tx_cfg.speed;
	txc->arb_mode = cl->tx_cfg.arb_mode;
}