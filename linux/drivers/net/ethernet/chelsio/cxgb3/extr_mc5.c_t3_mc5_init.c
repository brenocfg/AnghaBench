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
typedef  unsigned int u32 ;
struct mc5 {unsigned int tcam_size; scalar_t__ mode; int parity_enabled; int part_type; struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MC5_DB_CONFIG ; 
 int /*<<< orphan*/  A_MC5_DB_DBGI_REQ_ADDR1 ; 
 int /*<<< orphan*/  A_MC5_DB_DBGI_REQ_ADDR2 ; 
 int /*<<< orphan*/  A_MC5_DB_FILTER_TABLE ; 
 int /*<<< orphan*/  A_MC5_DB_ROUTING_TABLE_INDEX ; 
 int /*<<< orphan*/  A_MC5_DB_SERVER_INDEX ; 
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*,...) ; 
 int EINVAL ; 
 unsigned int F_TMMODE ; 
 int /*<<< orphan*/  F_TMRDY ; 
 unsigned int F_TMRST ; 
#define  IDT75N43102 129 
#define  IDT75P52100 128 
 unsigned int MAX_ROUTES ; 
 scalar_t__ MC5_MODE_72_BIT ; 
 unsigned int V_TMMODE (int) ; 
 int init_idt43102 (struct mc5*) ; 
 int init_idt52100 (struct mc5*) ; 
 int /*<<< orphan*/  mc5_dbgi_mode_disable (struct mc5*) ; 
 int /*<<< orphan*/  mc5_dbgi_mode_enable (struct mc5*) ; 
 unsigned int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ t3_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

int t3_mc5_init(struct mc5 *mc5, unsigned int nservers, unsigned int nfilters,
		unsigned int nroutes)
{
	u32 cfg;
	int err;
	unsigned int tcam_size = mc5->tcam_size;
	struct adapter *adap = mc5->adapter;

	if (!tcam_size)
		return 0;

	if (nroutes > MAX_ROUTES || nroutes + nservers + nfilters > tcam_size)
		return -EINVAL;

	/* Reset the TCAM */
	cfg = t3_read_reg(adap, A_MC5_DB_CONFIG) & ~F_TMMODE;
	cfg |= V_TMMODE(mc5->mode == MC5_MODE_72_BIT) | F_TMRST;
	t3_write_reg(adap, A_MC5_DB_CONFIG, cfg);
	if (t3_wait_op_done(adap, A_MC5_DB_CONFIG, F_TMRDY, 1, 500, 0)) {
		CH_ERR(adap, "TCAM reset timed out\n");
		return -1;
	}

	t3_write_reg(adap, A_MC5_DB_ROUTING_TABLE_INDEX, tcam_size - nroutes);
	t3_write_reg(adap, A_MC5_DB_FILTER_TABLE,
		     tcam_size - nroutes - nfilters);
	t3_write_reg(adap, A_MC5_DB_SERVER_INDEX,
		     tcam_size - nroutes - nfilters - nservers);

	mc5->parity_enabled = 1;

	/* All the TCAM addresses we access have only the low 32 bits non 0 */
	t3_write_reg(adap, A_MC5_DB_DBGI_REQ_ADDR1, 0);
	t3_write_reg(adap, A_MC5_DB_DBGI_REQ_ADDR2, 0);

	mc5_dbgi_mode_enable(mc5);

	switch (mc5->part_type) {
	case IDT75P52100:
		err = init_idt52100(mc5);
		break;
	case IDT75N43102:
		err = init_idt43102(mc5);
		break;
	default:
		CH_ERR(adap, "Unsupported TCAM type %d\n", mc5->part_type);
		err = -EINVAL;
		break;
	}

	mc5_dbgi_mode_disable(mc5);
	return err;
}