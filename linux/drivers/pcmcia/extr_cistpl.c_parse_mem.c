#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_5__ {int nwin; TYPE_1__* win; } ;
typedef  TYPE_2__ cistpl_mem_t ;
struct TYPE_4__ {int len; int card_addr; int host_addr; } ;

/* Variables and functions */

__attribute__((used)) static u_char *parse_mem(u_char *p, u_char *q, cistpl_mem_t *mem)
{
	int i, j, asz, lsz, has_ha;
	u_int len, ca, ha;

	if (p == q)
		return NULL;

	mem->nwin = (*p & 0x07) + 1;
	lsz = (*p & 0x18) >> 3;
	asz = (*p & 0x60) >> 5;
	has_ha = (*p & 0x80);
	if (++p == q)
		return NULL;

	for (i = 0; i < mem->nwin; i++) {
		len = ca = ha = 0;
		for (j = 0; j < lsz; j++, p++) {
			if (p == q)
				return NULL;
			len += *p << (j*8);
		}
		for (j = 0; j < asz; j++, p++) {
			if (p == q)
				return NULL;
			ca += *p << (j*8);
		}
		if (has_ha)
			for (j = 0; j < asz; j++, p++) {
				if (p == q)
					return NULL;
				ha += *p << (j*8);
			}
		mem->win[i].len = len << 8;
		mem->win[i].card_addr = ca << 8;
		mem->win[i].host_addr = ha << 8;
	}
	return p;
}