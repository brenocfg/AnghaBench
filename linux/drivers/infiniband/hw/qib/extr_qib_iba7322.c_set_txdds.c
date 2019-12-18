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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct txdds_ent {int amp; int main; int pre; int post; } ;
struct qib_pportdata {struct qib_devdata* dd; scalar_t__ hw_pidx; } ;
struct qib_devdata {int palign; } ;

/* Variables and functions */
 int DDS_ENT_AMP_LSB ; 
 int DDS_ENT_MAIN_LSB ; 
 int DDS_ENT_POST_LSB ; 
 int DDS_ENT_PRE_LSB ; 
 int /*<<< orphan*/  IBSD_DDS_MAP_TABLE ; 
 int KREG_IBPORT_IDX (int /*<<< orphan*/ ) ; 
 int kr_scratch ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int,int) ; 

__attribute__((used)) static void set_txdds(struct qib_pportdata *ppd, int ridx,
		      const struct txdds_ent *tp)
{
	struct qib_devdata *dd = ppd->dd;
	u32 pack_ent;
	int regidx;

	/* Get correct offset in chip-space, and in source table */
	regidx = KREG_IBPORT_IDX(IBSD_DDS_MAP_TABLE) + ridx;
	/*
	 * We do not use qib_write_kreg_port() because it was intended
	 * only for registers in the lower "port specific" pages.
	 * So do index calculation  by hand.
	 */
	if (ppd->hw_pidx)
		regidx += (dd->palign / sizeof(u64));

	pack_ent = tp->amp << DDS_ENT_AMP_LSB;
	pack_ent |= tp->main << DDS_ENT_MAIN_LSB;
	pack_ent |= tp->pre << DDS_ENT_PRE_LSB;
	pack_ent |= tp->post << DDS_ENT_POST_LSB;
	qib_write_kreg(dd, regidx, pack_ent);
	/* Prevent back-to-back writes by hitting scratch */
	qib_write_kreg(ppd->dd, kr_scratch, 0);
}