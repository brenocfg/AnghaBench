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
typedef  int u8 ;
struct mvpp2_port {int first_rxq; int /*<<< orphan*/  priv; int /*<<< orphan*/  id; } ;
struct mvpp2_cls_c2_entry {int act; int* attr; int valid; int /*<<< orphan*/ * tcam; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  c2 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP22_C2_FWD_SW_LOCK ; 
 int /*<<< orphan*/  MVPP22_C2_UPD ; 
 int /*<<< orphan*/  MVPP22_C2_UPD_LOCK ; 
 int MVPP22_CLS_C2_ACT_FWD (int /*<<< orphan*/ ) ; 
 int MVPP22_CLS_C2_ACT_QHIGH (int /*<<< orphan*/ ) ; 
 int MVPP22_CLS_C2_ACT_QLOW (int /*<<< orphan*/ ) ; 
 int MVPP22_CLS_C2_ACT_RSS_EN (int /*<<< orphan*/ ) ; 
 int MVPP22_CLS_C2_ATTR0_QHIGH (int) ; 
 int MVPP22_CLS_C2_ATTR0_QHIGH_MASK ; 
 int MVPP22_CLS_C2_ATTR0_QLOW (int) ; 
 int MVPP22_CLS_C2_ATTR0_QLOW_MASK ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_LU_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_PORT_ID (int) ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_RSS_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP22_CLS_LU_TYPE_ALL ; 
 int /*<<< orphan*/  MVPP2_CLS_LU_TYPE_MASK ; 
 int /*<<< orphan*/  memset (struct mvpp2_cls_c2_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_cls_c2_write (int /*<<< orphan*/ ,struct mvpp2_cls_c2_entry*) ; 

__attribute__((used)) static void mvpp2_port_c2_cls_init(struct mvpp2_port *port)
{
	struct mvpp2_cls_c2_entry c2;
	u8 qh, ql, pmap;

	memset(&c2, 0, sizeof(c2));

	c2.index = MVPP22_CLS_C2_RSS_ENTRY(port->id);

	pmap = BIT(port->id);
	c2.tcam[4] = MVPP22_CLS_C2_PORT_ID(pmap);
	c2.tcam[4] |= MVPP22_CLS_C2_TCAM_EN(MVPP22_CLS_C2_PORT_ID(pmap));

	/* Match on Lookup Type */
	c2.tcam[4] |= MVPP22_CLS_C2_TCAM_EN(MVPP22_CLS_C2_LU_TYPE(MVPP2_CLS_LU_TYPE_MASK));
	c2.tcam[4] |= MVPP22_CLS_C2_LU_TYPE(MVPP22_CLS_LU_TYPE_ALL);

	/* Update RSS status after matching this entry */
	c2.act = MVPP22_CLS_C2_ACT_RSS_EN(MVPP22_C2_UPD_LOCK);

	/* Mark packet as "forwarded to software", needed for RSS */
	c2.act |= MVPP22_CLS_C2_ACT_FWD(MVPP22_C2_FWD_SW_LOCK);

	/* Configure the default rx queue : Update Queue Low and Queue High, but
	 * don't lock, since the rx queue selection might be overridden by RSS
	 */
	c2.act |= MVPP22_CLS_C2_ACT_QHIGH(MVPP22_C2_UPD) |
		   MVPP22_CLS_C2_ACT_QLOW(MVPP22_C2_UPD);

	qh = (port->first_rxq >> 3) & MVPP22_CLS_C2_ATTR0_QHIGH_MASK;
	ql = port->first_rxq & MVPP22_CLS_C2_ATTR0_QLOW_MASK;

	c2.attr[0] = MVPP22_CLS_C2_ATTR0_QHIGH(qh) |
		      MVPP22_CLS_C2_ATTR0_QLOW(ql);

	c2.valid = true;

	mvpp2_cls_c2_write(port->priv, &c2);
}