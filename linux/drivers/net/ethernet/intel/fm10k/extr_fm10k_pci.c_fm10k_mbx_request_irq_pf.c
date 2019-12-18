#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct msix_entry {int entry; int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int (* register_handlers ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mbx; } ;
struct fm10k_intfc {struct fm10k_hw hw; struct net_device* netdev; struct msix_entry* msix_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_EIMR ; 
 int FM10K_EIMR_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM10K_INT_MAP (int /*<<< orphan*/ ) ; 
 int FM10K_INT_MAP_IMMEDIATE ; 
 int FM10K_INT_MAP_TIMER0 ; 
 int /*<<< orphan*/  FM10K_ITR (int) ; 
 int FM10K_ITR_ENABLE ; 
 size_t FM10K_MBX_VECTOR ; 
 int /*<<< orphan*/  FUM_FAULT ; 
 int /*<<< orphan*/  MAILBOX ; 
 int /*<<< orphan*/  MAXHOLDTIME ; 
 int /*<<< orphan*/  PCA_FAULT ; 
 int /*<<< orphan*/  SRAMERROR ; 
 int /*<<< orphan*/  SWITCHNOTREADY ; 
 int /*<<< orphan*/  SWITCHREADY ; 
 int /*<<< orphan*/  VFLR ; 
 int /*<<< orphan*/  fm10k_int_mailbox ; 
 int /*<<< orphan*/  fm10k_int_max_hold_time ; 
 int /*<<< orphan*/  fm10k_int_pcie_fault ; 
 int /*<<< orphan*/  fm10k_int_sram ; 
 int /*<<< orphan*/  fm10k_int_switch_up_down ; 
 int /*<<< orphan*/  fm10k_int_vflr ; 
 int /*<<< orphan*/  fm10k_msix_mbx_pf ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_err (struct fm10k_intfc*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  pf_mbx_data ; 
 int /*<<< orphan*/  probe ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fm10k_intfc*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm10k_mbx_request_irq_pf(struct fm10k_intfc *interface)
{
	struct msix_entry *entry = &interface->msix_entries[FM10K_MBX_VECTOR];
	struct net_device *dev = interface->netdev;
	struct fm10k_hw *hw = &interface->hw;
	int err;

	/* Use timer0 for interrupt moderation on the mailbox */
	u32 mbx_itr = entry->entry | FM10K_INT_MAP_TIMER0;
	u32 other_itr = entry->entry | FM10K_INT_MAP_IMMEDIATE;

	/* register mailbox handlers */
	err = hw->mbx.ops.register_handlers(&hw->mbx, pf_mbx_data);
	if (err)
		return err;

	/* request the IRQ */
	err = request_irq(entry->vector, fm10k_msix_mbx_pf, 0,
			  dev->name, interface);
	if (err) {
		netif_err(interface, probe, dev,
			  "request_irq for msix_mbx failed: %d\n", err);
		return err;
	}

	/* Enable interrupts w/ no moderation for "other" interrupts */
	fm10k_write_reg(hw, FM10K_INT_MAP(fm10k_int_pcie_fault), other_itr);
	fm10k_write_reg(hw, FM10K_INT_MAP(fm10k_int_switch_up_down), other_itr);
	fm10k_write_reg(hw, FM10K_INT_MAP(fm10k_int_sram), other_itr);
	fm10k_write_reg(hw, FM10K_INT_MAP(fm10k_int_max_hold_time), other_itr);
	fm10k_write_reg(hw, FM10K_INT_MAP(fm10k_int_vflr), other_itr);

	/* Enable interrupts w/ moderation for mailbox */
	fm10k_write_reg(hw, FM10K_INT_MAP(fm10k_int_mailbox), mbx_itr);

	/* Enable individual interrupt causes */
	fm10k_write_reg(hw, FM10K_EIMR, FM10K_EIMR_ENABLE(PCA_FAULT) |
					FM10K_EIMR_ENABLE(FUM_FAULT) |
					FM10K_EIMR_ENABLE(MAILBOX) |
					FM10K_EIMR_ENABLE(SWITCHREADY) |
					FM10K_EIMR_ENABLE(SWITCHNOTREADY) |
					FM10K_EIMR_ENABLE(SRAMERROR) |
					FM10K_EIMR_ENABLE(VFLR) |
					FM10K_EIMR_ENABLE(MAXHOLDTIME));

	/* enable interrupt */
	fm10k_write_reg(hw, FM10K_ITR(entry->entry), FM10K_ITR_ENABLE);

	return 0;
}