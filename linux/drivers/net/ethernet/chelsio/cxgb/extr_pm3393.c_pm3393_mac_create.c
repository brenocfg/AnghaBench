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
struct cmac {TYPE_1__* instance; int /*<<< orphan*/ * adapter; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {int fc; } ;
typedef  TYPE_1__ cmac_instance ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OFFSET (int) ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 struct cmac* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm3393_ops ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cmac *pm3393_mac_create(adapter_t *adapter, int index)
{
	struct cmac *cmac;

	cmac = kzalloc(sizeof(*cmac) + sizeof(cmac_instance), GFP_KERNEL);
	if (!cmac)
		return NULL;

	cmac->ops = &pm3393_ops;
	cmac->instance = (cmac_instance *) (cmac + 1);
	cmac->adapter = adapter;
	cmac->instance->fc = PAUSE_TX | PAUSE_RX;

	t1_tpi_write(adapter, OFFSET(0x0001), 0x00008000);
	t1_tpi_write(adapter, OFFSET(0x0001), 0x00000000);
	t1_tpi_write(adapter, OFFSET(0x2308), 0x00009800);
	t1_tpi_write(adapter, OFFSET(0x2305), 0x00001001);   /* PL4IO Enable */
	t1_tpi_write(adapter, OFFSET(0x2320), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2321), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2322), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2323), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2324), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2325), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2326), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2327), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2328), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x2329), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x232a), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x232b), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x232c), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x232d), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x232e), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x232f), 0x00008800);
	t1_tpi_write(adapter, OFFSET(0x230d), 0x00009c00);
	t1_tpi_write(adapter, OFFSET(0x2304), 0x00000202);	/* PL4IO Calendar Repetitions */

	t1_tpi_write(adapter, OFFSET(0x3200), 0x00008080);	/* EFLX Enable */
	t1_tpi_write(adapter, OFFSET(0x3210), 0x00000000);	/* EFLX Channel Deprovision */
	t1_tpi_write(adapter, OFFSET(0x3203), 0x00000000);	/* EFLX Low Limit */
	t1_tpi_write(adapter, OFFSET(0x3204), 0x00000040);	/* EFLX High Limit */
	t1_tpi_write(adapter, OFFSET(0x3205), 0x000002cc);	/* EFLX Almost Full */
	t1_tpi_write(adapter, OFFSET(0x3206), 0x00000199);	/* EFLX Almost Empty */
	t1_tpi_write(adapter, OFFSET(0x3207), 0x00000240);	/* EFLX Cut Through Threshold */
	t1_tpi_write(adapter, OFFSET(0x3202), 0x00000000);	/* EFLX Indirect Register Update */
	t1_tpi_write(adapter, OFFSET(0x3210), 0x00000001);	/* EFLX Channel Provision */
	t1_tpi_write(adapter, OFFSET(0x3208), 0x0000ffff);	/* EFLX Undocumented */
	t1_tpi_write(adapter, OFFSET(0x320a), 0x0000ffff);	/* EFLX Undocumented */
	t1_tpi_write(adapter, OFFSET(0x320c), 0x0000ffff);	/* EFLX enable overflow interrupt The other bit are undocumented */
	t1_tpi_write(adapter, OFFSET(0x320e), 0x0000ffff);	/* EFLX Undocumented */

	t1_tpi_write(adapter, OFFSET(0x2200), 0x0000c000);	/* IFLX Configuration - enable */
	t1_tpi_write(adapter, OFFSET(0x2201), 0x00000000);	/* IFLX Channel Deprovision */
	t1_tpi_write(adapter, OFFSET(0x220e), 0x00000000);	/* IFLX Low Limit */
	t1_tpi_write(adapter, OFFSET(0x220f), 0x00000100);	/* IFLX High Limit */
	t1_tpi_write(adapter, OFFSET(0x2210), 0x00000c00);	/* IFLX Almost Full Limit */
	t1_tpi_write(adapter, OFFSET(0x2211), 0x00000599);	/* IFLX Almost Empty Limit */
	t1_tpi_write(adapter, OFFSET(0x220d), 0x00000000);	/* IFLX Indirect Register Update */
	t1_tpi_write(adapter, OFFSET(0x2201), 0x00000001);	/* IFLX Channel Provision */
	t1_tpi_write(adapter, OFFSET(0x2203), 0x0000ffff);	/* IFLX Undocumented */
	t1_tpi_write(adapter, OFFSET(0x2205), 0x0000ffff);	/* IFLX Undocumented */
	t1_tpi_write(adapter, OFFSET(0x2209), 0x0000ffff);	/* IFLX Enable overflow interrupt.  The other bit are undocumented */

	t1_tpi_write(adapter, OFFSET(0x2241), 0xfffffffe);	/* PL4MOS Undocumented */
	t1_tpi_write(adapter, OFFSET(0x2242), 0x0000ffff);	/* PL4MOS Undocumented */
	t1_tpi_write(adapter, OFFSET(0x2243), 0x00000008);	/* PL4MOS Starving Burst Size */
	t1_tpi_write(adapter, OFFSET(0x2244), 0x00000008);	/* PL4MOS Hungry Burst Size */
	t1_tpi_write(adapter, OFFSET(0x2245), 0x00000008);	/* PL4MOS Transfer Size */
	t1_tpi_write(adapter, OFFSET(0x2240), 0x00000005);	/* PL4MOS Disable */

	t1_tpi_write(adapter, OFFSET(0x2280), 0x00002103);	/* PL4ODP Training Repeat and SOP rule */
	t1_tpi_write(adapter, OFFSET(0x2284), 0x00000000);	/* PL4ODP MAX_T setting */

	t1_tpi_write(adapter, OFFSET(0x3280), 0x00000087);	/* PL4IDU Enable data forward, port state machine. Set ALLOW_NON_ZERO_OLB */
	t1_tpi_write(adapter, OFFSET(0x3282), 0x0000001f);	/* PL4IDU Enable Dip4 check error interrupts */

	t1_tpi_write(adapter, OFFSET(0x3040), 0x0c32);	/* # TXXG Config */
	/* For T1 use timer based Mac flow control. */
	t1_tpi_write(adapter, OFFSET(0x304d), 0x8000);
	t1_tpi_write(adapter, OFFSET(0x2040), 0x059c);	/* # RXXG Config */
	t1_tpi_write(adapter, OFFSET(0x2049), 0x0001);	/* # RXXG Cut Through */
	t1_tpi_write(adapter, OFFSET(0x2070), 0x0000);	/* # Disable promiscuous mode */

	/* Setup Exact Match Filter 0 to allow broadcast packets.
	 */
	t1_tpi_write(adapter, OFFSET(0x206e), 0x0000);	/* # Disable Match Enable bit */
	t1_tpi_write(adapter, OFFSET(0x204a), 0xffff);	/* # low addr */
	t1_tpi_write(adapter, OFFSET(0x204b), 0xffff);	/* # mid addr */
	t1_tpi_write(adapter, OFFSET(0x204c), 0xffff);	/* # high addr */
	t1_tpi_write(adapter, OFFSET(0x206e), 0x0009);	/* # Enable Match Enable bit */

	t1_tpi_write(adapter, OFFSET(0x0003), 0x0000);	/* # NO SOP/ PAD_EN setup */
	t1_tpi_write(adapter, OFFSET(0x0100), 0x0ff0);	/* # RXEQB disabled */
	t1_tpi_write(adapter, OFFSET(0x0101), 0x0f0f);	/* # No Preemphasis */

	return cmac;
}