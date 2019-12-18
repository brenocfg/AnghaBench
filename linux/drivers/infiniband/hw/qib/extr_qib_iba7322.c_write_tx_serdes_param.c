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
typedef  int u64 ;
struct txdds_ent {int amp; int main; int post; int pre; } ;
struct qib_pportdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBSD_TX_DEEMPHASIS_OVERRIDE_0 ; 
 int SYM_LSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_RMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krp_tx_deemph_override ; 
 int qib_read_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tx_override_deemphasis_select ; 
 int /*<<< orphan*/  txampcntl_d2a ; 
 int /*<<< orphan*/  txc0_ena ; 
 int /*<<< orphan*/  txcn1_ena ; 
 int /*<<< orphan*/  txcp1_ena ; 

__attribute__((used)) static void write_tx_serdes_param(struct qib_pportdata *ppd,
				  struct txdds_ent *txdds)
{
	u64 deemph;

	deemph = qib_read_kreg_port(ppd, krp_tx_deemph_override);
	/* field names for amp, main, post, pre, respectively */
	deemph &= ~(SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txampcntl_d2a) |
		    SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txc0_ena) |
		    SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txcp1_ena) |
		    SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txcn1_ena));

	deemph |= SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
			   tx_override_deemphasis_select);
	deemph |= (txdds->amp & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		    txampcntl_d2a)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				       txampcntl_d2a);
	deemph |= (txdds->main & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		     txc0_ena)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				   txc0_ena);
	deemph |= (txdds->post & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		     txcp1_ena)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				    txcp1_ena);
	deemph |= (txdds->pre & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		     txcn1_ena)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				    txcn1_ena);
	qib_write_kreg_port(ppd, krp_tx_deemph_override, deemph);
}