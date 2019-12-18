#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tb_switch {int dummy; } ;
struct TYPE_4__ {int vsec_id; int next; int /*<<< orphan*/  length; } ;
struct TYPE_3__ {int vsec_id; int next; } ;
struct tb_cap_any {TYPE_2__ extended_short; TYPE_1__ extended_long; } ;
typedef  enum tb_switch_vse_cap { ____Placeholder_tb_switch_vse_cap } tb_switch_vse_cap ;

/* Variables and functions */
 int CAP_OFFSET_MAX ; 
 int ENOENT ; 
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int /*<<< orphan*/  TB_SWITCH_CAP_VSE ; 
 int VSE_CAP_OFFSET_MAX ; 
 int tb_sw_read (struct tb_switch*,struct tb_cap_any*,int /*<<< orphan*/ ,int,int) ; 
 int tb_switch_find_cap (struct tb_switch*,int /*<<< orphan*/ ) ; 

int tb_switch_find_vse_cap(struct tb_switch *sw, enum tb_switch_vse_cap vsec)
{
	struct tb_cap_any header;
	int offset;

	offset = tb_switch_find_cap(sw, TB_SWITCH_CAP_VSE);
	if (offset < 0)
		return offset;

	while (offset > 0 && offset < VSE_CAP_OFFSET_MAX) {
		int ret;

		ret = tb_sw_read(sw, &header, TB_CFG_SWITCH, offset, 2);
		if (ret)
			return ret;

		/*
		 * Extended vendor specific capabilities come in two
		 * flavors: short and long. The latter is used when
		 * offset is over 0xff.
		 */
		if (offset >= CAP_OFFSET_MAX) {
			if (header.extended_long.vsec_id == vsec)
				return offset;
			offset = header.extended_long.next;
		} else {
			if (header.extended_short.vsec_id == vsec)
				return offset;
			if (!header.extended_short.length)
				return -ENOENT;
			offset = header.extended_short.next;
		}
	}

	return -ENOENT;
}