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
typedef  int /*<<< orphan*/  sysfreq ;
struct TYPE_2__ {int bi_busfreq; int bi_ipbfreq; int /*<<< orphan*/  bi_intfreq; int /*<<< orphan*/  bi_enetaddr; int /*<<< orphan*/  bi_memsize; int /*<<< orphan*/  bi_memstart; } ;

/* Variables and functions */
 TYPE_1__ bd ; 
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dt_fixup_mac_addresses (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_xlate_reg (void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 void* find_node_by_compatible (int /*<<< orphan*/ *,char*) ; 
 void* find_node_by_devtype (int /*<<< orphan*/ *,char*) ; 
 int in_8 (void*) ; 
 int /*<<< orphan*/  setprop (void*,char*,int*,int) ; 

__attribute__((used)) static void platform_fixups(void)
{
	void *soc, *reg;
	int div;
	u32 sysfreq;


	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_addresses(bd.bi_enetaddr);
	dt_fixup_cpu_clocks(bd.bi_intfreq, bd.bi_busfreq / 4, bd.bi_busfreq);

	/* Unfortunately, the specific model number is encoded in the
	 * soc node name in existing dts files -- once that is fixed,
	 * this can do a simple path lookup.
	 */
	soc = find_node_by_devtype(NULL, "soc");
	if (!soc)
		soc = find_node_by_compatible(NULL, "fsl,mpc5200-immr");
	if (!soc)
		soc = find_node_by_compatible(NULL, "fsl,mpc5200b-immr");
	if (soc) {
		setprop(soc, "bus-frequency", &bd.bi_ipbfreq,
			sizeof(bd.bi_ipbfreq));

		if (!dt_xlate_reg(soc, 0, (void*)&reg, NULL))
			return;
		div = in_8(reg + 0x204) & 0x0020 ? 8 : 4;
		sysfreq = bd.bi_busfreq * div;
		setprop(soc, "system-frequency", &sysfreq, sizeof(sysfreq));
	}
}