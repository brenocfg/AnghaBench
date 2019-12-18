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
typedef  int u32 ;
struct tb_switch {int generation; int cap_lc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int TB_LC_DESC_NLC_MASK ; 
 int TB_LC_DESC_PORT_SIZE_MASK ; 
 int TB_LC_DESC_PORT_SIZE_SHIFT ; 
 int TB_LC_DESC_SIZE_MASK ; 
 int TB_LC_DESC_SIZE_SHIFT ; 
 scalar_t__ TB_LC_SX_CTRL ; 
 int TB_LC_SX_CTRL_SLP ; 
 int read_lc_desc (struct tb_switch*,int*) ; 
 int tb_sw_read (struct tb_switch*,int*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int tb_sw_write (struct tb_switch*,int*,int /*<<< orphan*/ ,scalar_t__,int) ; 

int tb_lc_set_sleep(struct tb_switch *sw)
{
	int start, size, nlc, ret, i;
	u32 desc;

	if (sw->generation < 2)
		return 0;

	ret = read_lc_desc(sw, &desc);
	if (ret)
		return ret;

	/* Figure out number of link controllers */
	nlc = desc & TB_LC_DESC_NLC_MASK;
	start = (desc & TB_LC_DESC_SIZE_MASK) >> TB_LC_DESC_SIZE_SHIFT;
	size = (desc & TB_LC_DESC_PORT_SIZE_MASK) >> TB_LC_DESC_PORT_SIZE_SHIFT;

	/* For each link controller set sleep bit */
	for (i = 0; i < nlc; i++) {
		unsigned int offset = sw->cap_lc + start + i * size;
		u32 ctrl;

		ret = tb_sw_read(sw, &ctrl, TB_CFG_SWITCH,
				 offset + TB_LC_SX_CTRL, 1);
		if (ret)
			return ret;

		ctrl |= TB_LC_SX_CTRL_SLP;
		ret = tb_sw_write(sw, &ctrl, TB_CFG_SWITCH,
				  offset + TB_LC_SX_CTRL, 1);
		if (ret)
			return ret;
	}

	return 0;
}