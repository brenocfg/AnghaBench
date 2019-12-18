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
struct TYPE_2__ {int decimal; int /*<<< orphan*/  integer; } ;
struct isif_linearize {int corr_shft; int /*<<< orphan*/ * table; TYPE_1__ scale_fact; int /*<<< orphan*/  en; } ;

/* Variables and functions */
 int ISIF_LINEAR_TAB_SIZE ; 
 int ISIF_LIN_CORRSFT_SHIFT ; 
 int ISIF_LIN_SCALE_FACT_INTEG_SHIFT ; 
 int /*<<< orphan*/  LINCFG0 ; 
 int /*<<< orphan*/  LINCFG1 ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw_lin_tbl (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void isif_config_linearization(struct isif_linearize *linearize)
{
	u32 val, i;

	if (!linearize->en) {
		regw(0, LINCFG0);
		return;
	}

	/* shift value for correction & enable linearization (set lsb) */
	val = (linearize->corr_shft << ISIF_LIN_CORRSFT_SHIFT) | 1;
	regw(val, LINCFG0);

	/* Scale factor */
	val = ((!!linearize->scale_fact.integer) <<
	       ISIF_LIN_SCALE_FACT_INTEG_SHIFT) |
	       linearize->scale_fact.decimal;
	regw(val, LINCFG1);

	for (i = 0; i < ISIF_LINEAR_TAB_SIZE; i++) {
		if (i % 2)
			regw_lin_tbl(linearize->table[i], ((i >> 1) << 2), 1);
		else
			regw_lin_tbl(linearize->table[i], ((i >> 1) << 2), 0);
	}
}