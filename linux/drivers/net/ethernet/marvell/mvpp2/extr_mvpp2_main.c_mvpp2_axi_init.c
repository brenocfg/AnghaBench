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
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP22_AXI_AGGRQ_DESCR_RD_ATTR_REG ; 
 int MVPP22_AXI_ATTR_CACHE_OFFS ; 
 int MVPP22_AXI_ATTR_DOMAIN_OFFS ; 
 int /*<<< orphan*/  MVPP22_AXI_BM_RD_ATTR_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_BM_WR_ATTR_REG ; 
 int MVPP22_AXI_CODE_CACHE_NON_CACHE ; 
 int MVPP22_AXI_CODE_CACHE_OFFS ; 
 int MVPP22_AXI_CODE_CACHE_RD_CACHE ; 
 int MVPP22_AXI_CODE_CACHE_WR_CACHE ; 
 int MVPP22_AXI_CODE_DOMAIN_OFFS ; 
 int MVPP22_AXI_CODE_DOMAIN_OUTER_DOM ; 
 int MVPP22_AXI_CODE_DOMAIN_SYSTEM ; 
 int /*<<< orphan*/  MVPP22_AXI_RD_NORMAL_CODE_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_RD_SNOOP_CODE_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_RXQ_DESCR_WR_ATTR_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_RX_DATA_WR_ATTR_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_TXQ_DESCR_RD_ATTR_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_TXQ_DESCR_WR_ATTR_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_TX_DATA_RD_ATTR_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_WR_NORMAL_CODE_REG ; 
 int /*<<< orphan*/  MVPP22_AXI_WR_SNOOP_CODE_REG ; 
 int /*<<< orphan*/  MVPP22_BM_ADDR_HIGH_RLS_REG ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvpp2_axi_init(struct mvpp2 *priv)
{
	u32 val, rdval, wrval;

	mvpp2_write(priv, MVPP22_BM_ADDR_HIGH_RLS_REG, 0x0);

	/* AXI Bridge Configuration */

	rdval = MVPP22_AXI_CODE_CACHE_RD_CACHE
		<< MVPP22_AXI_ATTR_CACHE_OFFS;
	rdval |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_ATTR_DOMAIN_OFFS;

	wrval = MVPP22_AXI_CODE_CACHE_WR_CACHE
		<< MVPP22_AXI_ATTR_CACHE_OFFS;
	wrval |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_ATTR_DOMAIN_OFFS;

	/* BM */
	mvpp2_write(priv, MVPP22_AXI_BM_WR_ATTR_REG, wrval);
	mvpp2_write(priv, MVPP22_AXI_BM_RD_ATTR_REG, rdval);

	/* Descriptors */
	mvpp2_write(priv, MVPP22_AXI_AGGRQ_DESCR_RD_ATTR_REG, rdval);
	mvpp2_write(priv, MVPP22_AXI_TXQ_DESCR_WR_ATTR_REG, wrval);
	mvpp2_write(priv, MVPP22_AXI_TXQ_DESCR_RD_ATTR_REG, rdval);
	mvpp2_write(priv, MVPP22_AXI_RXQ_DESCR_WR_ATTR_REG, wrval);

	/* Buffer Data */
	mvpp2_write(priv, MVPP22_AXI_TX_DATA_RD_ATTR_REG, rdval);
	mvpp2_write(priv, MVPP22_AXI_RX_DATA_WR_ATTR_REG, wrval);

	val = MVPP22_AXI_CODE_CACHE_NON_CACHE
		<< MVPP22_AXI_CODE_CACHE_OFFS;
	val |= MVPP22_AXI_CODE_DOMAIN_SYSTEM
		<< MVPP22_AXI_CODE_DOMAIN_OFFS;
	mvpp2_write(priv, MVPP22_AXI_RD_NORMAL_CODE_REG, val);
	mvpp2_write(priv, MVPP22_AXI_WR_NORMAL_CODE_REG, val);

	val = MVPP22_AXI_CODE_CACHE_RD_CACHE
		<< MVPP22_AXI_CODE_CACHE_OFFS;
	val |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_CODE_DOMAIN_OFFS;

	mvpp2_write(priv, MVPP22_AXI_RD_SNOOP_CODE_REG, val);

	val = MVPP22_AXI_CODE_CACHE_WR_CACHE
		<< MVPP22_AXI_CODE_CACHE_OFFS;
	val |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_CODE_DOMAIN_OFFS;

	mvpp2_write(priv, MVPP22_AXI_WR_SNOOP_CODE_REG, val);
}