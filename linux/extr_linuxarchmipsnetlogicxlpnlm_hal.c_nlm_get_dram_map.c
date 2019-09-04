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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 unsigned int BRIDGE_9XX_DRAM_BAR (int) ; 
 unsigned int BRIDGE_9XX_DRAM_LIMIT (int) ; 
 unsigned int BRIDGE_9XX_DRAM_NODE_TRANSLN (int) ; 
 unsigned int BRIDGE_DRAM_BAR (int) ; 
 unsigned int BRIDGE_DRAM_LIMIT (int) ; 
 unsigned int BRIDGE_DRAM_NODE_TRANSLN (int) ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 int nlm_get_bridge_regbase (int /*<<< orphan*/ ) ; 
 int nlm_read_bridge_reg (int,unsigned int) ; 

int nlm_get_dram_map(int node, uint64_t *dram_map, int nentries)
{
	uint64_t bridgebase, base, lim;
	uint32_t val;
	unsigned int barreg, limreg, xlatreg;
	int i, n, rv;

	/* Look only at mapping on Node 0, we don't handle crazy configs */
	bridgebase = nlm_get_bridge_regbase(0);
	rv = 0;
	for (i = 0; i < 8; i++) {
		if (rv + 1 >= nentries)
			break;
		if (cpu_is_xlp9xx()) {
			barreg = BRIDGE_9XX_DRAM_BAR(i);
			limreg = BRIDGE_9XX_DRAM_LIMIT(i);
			xlatreg = BRIDGE_9XX_DRAM_NODE_TRANSLN(i);
		} else {
			barreg = BRIDGE_DRAM_BAR(i);
			limreg = BRIDGE_DRAM_LIMIT(i);
			xlatreg = BRIDGE_DRAM_NODE_TRANSLN(i);
		}
		if (node >= 0) {
			/* node specified, get node mapping of BAR */
			val = nlm_read_bridge_reg(bridgebase, xlatreg);
			n = (val >> 1) & 0x3;
			if (n != node)
				continue;
		}
		val = nlm_read_bridge_reg(bridgebase, barreg);
		val = (val >>  12) & 0xfffff;
		base = (uint64_t) val << 20;
		val = nlm_read_bridge_reg(bridgebase, limreg);
		val = (val >>  12) & 0xfffff;
		if (val == 0)   /* BAR not used */
			continue;
		lim = ((uint64_t)val + 1) << 20;
		dram_map[rv] = base;
		dram_map[rv + 1] = lim;
		rv += 2;
	}
	return rv;
}