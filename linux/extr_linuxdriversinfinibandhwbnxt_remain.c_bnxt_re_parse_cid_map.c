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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void bnxt_re_parse_cid_map(u8 prio_map, u8 *cid_map, u16 *cosq)
{
	u16 prio;
	u8 id;

	for (prio = 0, id = 0; prio < 8; prio++) {
		if (prio_map & (1 << prio)) {
			cosq[id] = cid_map[prio];
			id++;
			if (id == 2) /* Max 2 tcs supported */
				break;
		}
	}
}