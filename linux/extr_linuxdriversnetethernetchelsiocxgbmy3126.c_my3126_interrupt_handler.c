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
typedef  int u16 ;
struct cphy {int count; int bmsr; int elmer_gpo; int act_count; int act_on; int /*<<< orphan*/ * adapter; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPO ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int MDIO_STAT1_LSTATUS ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ) ; 
 int SUNI1x10GEXP_BITMSK_MSTAT_SNAP ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_CONTROL ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_COUNTER_1_LOW ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_COUNTER_33_LOW ; 
 int cphy_cause_link_change ; 
 int /*<<< orphan*/  cphy_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ is_T2 (int /*<<< orphan*/ *) ; 
 scalar_t__ t1_is_T1B (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_link_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int my3126_interrupt_handler(struct cphy *cphy)
{
	u32 val;
	u16 val16;
	u16 status;
	u32 act_count;
	adapter_t *adapter;
	adapter = cphy->adapter;

	if (cphy->count == 50) {
		cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
		val16 = (u16) val;
		status = cphy->bmsr ^ val16;

		if (status & MDIO_STAT1_LSTATUS)
			t1_link_changed(adapter, 0);
		cphy->bmsr = val16;

		/* We have only enabled link change interrupts so it
		   must be that
		 */
		cphy->count = 0;
	}

	t1_tpi_write(adapter, OFFSET(SUNI1x10GEXP_REG_MSTAT_CONTROL),
		SUNI1x10GEXP_BITMSK_MSTAT_SNAP);
	t1_tpi_read(adapter,
		OFFSET(SUNI1x10GEXP_REG_MSTAT_COUNTER_1_LOW), &act_count);
	t1_tpi_read(adapter,
		OFFSET(SUNI1x10GEXP_REG_MSTAT_COUNTER_33_LOW), &val);
	act_count += val;

	/* Populate elmer_gpo with the register value */
	t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	cphy->elmer_gpo = val;

	if ( (val & (1 << 8)) || (val & (1 << 19)) ||
	     (cphy->act_count == act_count) || cphy->act_on ) {
		if (is_T2(adapter))
			val |= (1 << 9);
		else if (t1_is_T1B(adapter))
			val |= (1 << 20);
		cphy->act_on = 0;
	} else {
		if (is_T2(adapter))
			val &= ~(1 << 9);
		else if (t1_is_T1B(adapter))
			val &= ~(1 << 20);
		cphy->act_on = 1;
	}

	t1_tpi_write(adapter, A_ELMER0_GPO, val);

	cphy->elmer_gpo = val;
	cphy->act_count = act_count;
	cphy->count++;

	return cphy_cause_link_change;
}