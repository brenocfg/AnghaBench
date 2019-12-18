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
struct memac_cfg {int reset_on_init; int promiscuous_mode_enable; int pause_ignore; int /*<<< orphan*/  pause_quanta; int /*<<< orphan*/  max_frame_length; int /*<<< orphan*/  tx_ipg_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FRAME_LENGTH ; 
 int /*<<< orphan*/  DEFAULT_PAUSE_QUANTA ; 
 int /*<<< orphan*/  DEFAULT_TX_IPG_LENGTH ; 

__attribute__((used)) static void set_dflts(struct memac_cfg *cfg)
{
	cfg->reset_on_init = false;
	cfg->promiscuous_mode_enable = false;
	cfg->pause_ignore = false;
	cfg->tx_ipg_length = DEFAULT_TX_IPG_LENGTH;
	cfg->max_frame_length = DEFAULT_FRAME_LENGTH;
	cfg->pause_quanta = DEFAULT_PAUSE_QUANTA;
}