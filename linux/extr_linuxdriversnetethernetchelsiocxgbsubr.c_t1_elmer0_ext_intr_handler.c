#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int u32 ;
struct cphy {TYPE_1__* ops; } ;
struct cmac {TYPE_3__* ops; } ;
struct TYPE_19__ {TYPE_4__* pdev; TYPE_2__* port; } ;
typedef  TYPE_5__ adapter_t ;
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* interrupt_handler ) (struct cmac*) ;} ;
struct TYPE_16__ {struct cmac* mac; struct cphy* phy; } ;
struct TYPE_15__ {int (* interrupt_handler ) (struct cphy*) ;} ;
struct TYPE_14__ {int board; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPI_STAT ; 
 int /*<<< orphan*/  A_ELMER0_INT_CAUSE ; 
#define  CHBT_BOARD_8000 132 
#define  CHBT_BOARD_CHT110 131 
#define  CHBT_BOARD_CHT210 130 
#define  CHBT_BOARD_N110 129 
#define  CHBT_BOARD_N210 128 
 int ELMER0_GP_BIT1 ; 
 int ELMER0_GP_BIT5 ; 
 int ELMER0_GP_BIT6 ; 
 TYPE_12__* board_info (TYPE_5__*) ; 
 int cphy_cause_link_change ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  netif_msg_intr (TYPE_5__*) ; 
 int /*<<< orphan*/  netif_msg_link (TYPE_5__*) ; 
 int stub1 (struct cphy*) ; 
 int /*<<< orphan*/  stub2 (struct cmac*) ; 
 int /*<<< orphan*/  t1_link_changed (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_tpi_read (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t1_tpi_write (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

int t1_elmer0_ext_intr_handler(adapter_t *adapter)
{
	struct cphy *phy;
	int phy_cause;
	u32 cause;

	t1_tpi_read(adapter, A_ELMER0_INT_CAUSE, &cause);

	switch (board_info(adapter)->board) {
#ifdef CONFIG_CHELSIO_T1_1G
	case CHBT_BOARD_CHT204:
	case CHBT_BOARD_CHT204E:
	case CHBT_BOARD_CHN204:
	case CHBT_BOARD_CHT204V: {
		int i, port_bit;
		for_each_port(adapter, i) {
			port_bit = i + 1;
			if (!(cause & (1 << port_bit)))
				continue;

			phy = adapter->port[i].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, i);
		}
		break;
	}
	case CHBT_BOARD_CHT101:
		if (cause & ELMER0_GP_BIT1) { /* Marvell 88E1111 interrupt */
			phy = adapter->port[0].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, 0);
		}
		break;
	case CHBT_BOARD_7500: {
		int p;
		/*
		 * Elmer0's interrupt cause isn't useful here because there is
		 * only one bit that can be set for all 4 ports.  This means
		 * we are forced to check every PHY's interrupt status
		 * register to see who initiated the interrupt.
		 */
		for_each_port(adapter, p) {
			phy = adapter->port[p].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
			    t1_link_changed(adapter, p);
		}
		break;
	}
#endif
	case CHBT_BOARD_CHT210:
	case CHBT_BOARD_N210:
	case CHBT_BOARD_N110:
		if (cause & ELMER0_GP_BIT6) { /* Marvell 88x2010 interrupt */
			phy = adapter->port[0].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, 0);
		}
		break;
	case CHBT_BOARD_8000:
	case CHBT_BOARD_CHT110:
		if (netif_msg_intr(adapter))
			dev_dbg(&adapter->pdev->dev,
				"External interrupt cause 0x%x\n", cause);
		if (cause & ELMER0_GP_BIT1) {        /* PMC3393 INTB */
			struct cmac *mac = adapter->port[0].mac;

			mac->ops->interrupt_handler(mac);
		}
		if (cause & ELMER0_GP_BIT5) {        /* XPAK MOD_DETECT */
			u32 mod_detect;

			t1_tpi_read(adapter,
					A_ELMER0_GPI_STAT, &mod_detect);
			if (netif_msg_link(adapter))
				dev_info(&adapter->pdev->dev, "XPAK %s\n",
					 mod_detect ? "removed" : "inserted");
		}
		break;
	}
	t1_tpi_write(adapter, A_ELMER0_INT_CAUSE, cause);
	return 0;
}