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
 int FM10K_INT_MAP_TIMER0 ; 
 int FM10K_ITR_ENABLE ; 
 size_t FM10K_MBX_VECTOR ; 
 int /*<<< orphan*/  FM10K_VFINT_MAP ; 
 int /*<<< orphan*/  FM10K_VFITR (int) ; 
 int /*<<< orphan*/  fm10k_msix_mbx_vf ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_err (struct fm10k_intfc*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  probe ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fm10k_intfc*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf_mbx_data ; 

__attribute__((used)) static int fm10k_mbx_request_irq_vf(struct fm10k_intfc *interface)
{
	struct msix_entry *entry = &interface->msix_entries[FM10K_MBX_VECTOR];
	struct net_device *dev = interface->netdev;
	struct fm10k_hw *hw = &interface->hw;
	int err;

	/* Use timer0 for interrupt moderation on the mailbox */
	u32 itr = entry->entry | FM10K_INT_MAP_TIMER0;

	/* register mailbox handlers */
	err = hw->mbx.ops.register_handlers(&hw->mbx, vf_mbx_data);
	if (err)
		return err;

	/* request the IRQ */
	err = request_irq(entry->vector, fm10k_msix_mbx_vf, 0,
			  dev->name, interface);
	if (err) {
		netif_err(interface, probe, dev,
			  "request_irq for msix_mbx failed: %d\n", err);
		return err;
	}

	/* map all of the interrupt sources */
	fm10k_write_reg(hw, FM10K_VFINT_MAP, itr);

	/* enable interrupt */
	fm10k_write_reg(hw, FM10K_VFITR(entry->entry), FM10K_ITR_ENABLE);

	return 0;
}