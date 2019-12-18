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
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN6I_DSI_BASIC_CTL0_INST_ST ; 
 int /*<<< orphan*/  SUN6I_DSI_BASIC_CTL0_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun6i_dsi_inst_commit(struct sun6i_dsi *dsi)
{
	regmap_update_bits(dsi->regs, SUN6I_DSI_BASIC_CTL0_REG,
			   SUN6I_DSI_BASIC_CTL0_INST_ST,
			   SUN6I_DSI_BASIC_CTL0_INST_ST);
}