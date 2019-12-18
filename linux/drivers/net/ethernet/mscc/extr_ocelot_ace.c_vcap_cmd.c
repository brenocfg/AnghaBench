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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ocelot {int dummy; } ;
struct TYPE_2__ {scalar_t__ entry_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  S2_CORE_UPDATE_CTRL ; 
 int S2_CORE_UPDATE_CTRL_UPDATE_ACTION_DIS ; 
 int S2_CORE_UPDATE_CTRL_UPDATE_ADDR (scalar_t__) ; 
 int S2_CORE_UPDATE_CTRL_UPDATE_CMD (int) ; 
 int S2_CORE_UPDATE_CTRL_UPDATE_CNT_DIS ; 
 int S2_CORE_UPDATE_CTRL_UPDATE_ENTRY_DIS ; 
 int S2_CORE_UPDATE_CTRL_UPDATE_SHOT ; 
 int VCAP_SEL_ACTION ; 
 int VCAP_SEL_COUNTER ; 
 int VCAP_SEL_ENTRY ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readx_poll_timeout (int /*<<< orphan*/ ,struct ocelot*,int,int,int,int) ; 
 TYPE_1__ vcap_is2 ; 
 int /*<<< orphan*/  vcap_s2_read_update_ctrl ; 

__attribute__((used)) static void vcap_cmd(struct ocelot *oc, u16 ix, int cmd, int sel)
{
	u32 value = (S2_CORE_UPDATE_CTRL_UPDATE_CMD(cmd) |
		     S2_CORE_UPDATE_CTRL_UPDATE_ADDR(ix) |
		     S2_CORE_UPDATE_CTRL_UPDATE_SHOT);

	if ((sel & VCAP_SEL_ENTRY) && ix >= vcap_is2.entry_count)
		return;

	if (!(sel & VCAP_SEL_ENTRY))
		value |= S2_CORE_UPDATE_CTRL_UPDATE_ENTRY_DIS;

	if (!(sel & VCAP_SEL_ACTION))
		value |= S2_CORE_UPDATE_CTRL_UPDATE_ACTION_DIS;

	if (!(sel & VCAP_SEL_COUNTER))
		value |= S2_CORE_UPDATE_CTRL_UPDATE_CNT_DIS;

	ocelot_write(oc, value, S2_CORE_UPDATE_CTRL);
	readx_poll_timeout(vcap_s2_read_update_ctrl, oc, value,
				(value & S2_CORE_UPDATE_CTRL_UPDATE_SHOT) == 0,
				10, 100000);
}