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
struct tgec_cfg {int promiscuous_mode_enable; int pause_ignore; int /*<<< orphan*/  pause_quant; int /*<<< orphan*/  max_frame_length; int /*<<< orphan*/  tx_ipg_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MAX_FRAME_LENGTH ; 
 int /*<<< orphan*/  DEFAULT_PAUSE_QUANT ; 
 int /*<<< orphan*/  DEFAULT_TX_IPG_LENGTH ; 

__attribute__((used)) static void set_dflts(struct tgec_cfg *cfg)
{
	cfg->promiscuous_mode_enable = false;
	cfg->pause_ignore = false;
	cfg->tx_ipg_length = DEFAULT_TX_IPG_LENGTH;
	cfg->max_frame_length = DEFAULT_MAX_FRAME_LENGTH;
	cfg->pause_quant = DEFAULT_PAUSE_QUANT;
}