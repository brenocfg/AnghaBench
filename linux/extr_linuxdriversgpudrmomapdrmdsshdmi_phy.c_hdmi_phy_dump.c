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
struct seq_file {int dummy; } ;
struct hdmi_phy_data {int /*<<< orphan*/  base; TYPE_1__* features; } ;
struct TYPE_2__ {scalar_t__ bist_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_TXPHY_BIST_CONTROL ; 
 int /*<<< orphan*/  HDMI_TXPHY_DIGITAL_CTRL ; 
 int /*<<< orphan*/  HDMI_TXPHY_PAD_CFG_CTRL ; 
 int /*<<< orphan*/  HDMI_TXPHY_POWER_CTRL ; 
 int /*<<< orphan*/  HDMI_TXPHY_TX_CTRL ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 

void hdmi_phy_dump(struct hdmi_phy_data *phy, struct seq_file *s)
{
#define DUMPPHY(r) seq_printf(s, "%-35s %08x\n", #r,\
		hdmi_read_reg(phy->base, r))

	DUMPPHY(HDMI_TXPHY_TX_CTRL);
	DUMPPHY(HDMI_TXPHY_DIGITAL_CTRL);
	DUMPPHY(HDMI_TXPHY_POWER_CTRL);
	DUMPPHY(HDMI_TXPHY_PAD_CFG_CTRL);
	if (phy->features->bist_ctrl)
		DUMPPHY(HDMI_TXPHY_BIST_CONTROL);
}