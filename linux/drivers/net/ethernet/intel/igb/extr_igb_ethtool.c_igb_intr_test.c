#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int type; } ;
struct e1000_hw {TYPE_2__ mac; } ;
struct igb_adapter {int flags; int test_icr; TYPE_3__* msix_entries; TYPE_1__* pdev; struct net_device* netdev; struct e1000_hw hw; } ;
struct TYPE_6__ {int vector; } ;
struct TYPE_4__ {int irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_ICS ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_IMS ; 
 int IGB_FLAG_HAS_MSI ; 
 int IGB_FLAG_HAS_MSIX ; 
 int /*<<< orphan*/  IRQF_PROBE_SHARED ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 int /*<<< orphan*/  free_irq (int,struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_test_intr ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct igb_adapter*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static int igb_intr_test(struct igb_adapter *adapter, u64 *data)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	u32 mask, ics_mask, i = 0, shared_int = true;
	u32 irq = adapter->pdev->irq;

	*data = 0;

	/* Hook up test interrupt handler just for this test */
	if (adapter->flags & IGB_FLAG_HAS_MSIX) {
		if (request_irq(adapter->msix_entries[0].vector,
				igb_test_intr, 0, netdev->name, adapter)) {
			*data = 1;
			return -1;
		}
	} else if (adapter->flags & IGB_FLAG_HAS_MSI) {
		shared_int = false;
		if (request_irq(irq,
				igb_test_intr, 0, netdev->name, adapter)) {
			*data = 1;
			return -1;
		}
	} else if (!request_irq(irq, igb_test_intr, IRQF_PROBE_SHARED,
				netdev->name, adapter)) {
		shared_int = false;
	} else if (request_irq(irq, igb_test_intr, IRQF_SHARED,
		 netdev->name, adapter)) {
		*data = 1;
		return -1;
	}
	dev_info(&adapter->pdev->dev, "testing %s interrupt\n",
		(shared_int ? "shared" : "unshared"));

	/* Disable all the interrupts */
	wr32(E1000_IMC, ~0);
	wrfl();
	usleep_range(10000, 11000);

	/* Define all writable bits for ICS */
	switch (hw->mac.type) {
	case e1000_82575:
		ics_mask = 0x37F47EDD;
		break;
	case e1000_82576:
		ics_mask = 0x77D4FBFD;
		break;
	case e1000_82580:
		ics_mask = 0x77DCFED5;
		break;
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
		ics_mask = 0x77DCFED5;
		break;
	default:
		ics_mask = 0x7FFFFFFF;
		break;
	}

	/* Test each interrupt */
	for (; i < 31; i++) {
		/* Interrupt to test */
		mask = BIT(i);

		if (!(mask & ics_mask))
			continue;

		if (!shared_int) {
			/* Disable the interrupt to be reported in
			 * the cause register and then force the same
			 * interrupt and see if one gets posted.  If
			 * an interrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;

			/* Flush any pending interrupts */
			wr32(E1000_ICR, ~0);

			wr32(E1000_IMC, mask);
			wr32(E1000_ICS, mask);
			wrfl();
			usleep_range(10000, 11000);

			if (adapter->test_icr & mask) {
				*data = 3;
				break;
			}
		}

		/* Enable the interrupt to be reported in
		 * the cause register and then force the same
		 * interrupt and see if one gets posted.  If
		 * an interrupt was not posted to the bus, the
		 * test failed.
		 */
		adapter->test_icr = 0;

		/* Flush any pending interrupts */
		wr32(E1000_ICR, ~0);

		wr32(E1000_IMS, mask);
		wr32(E1000_ICS, mask);
		wrfl();
		usleep_range(10000, 11000);

		if (!(adapter->test_icr & mask)) {
			*data = 4;
			break;
		}

		if (!shared_int) {
			/* Disable the other interrupts to be reported in
			 * the cause register and then force the other
			 * interrupts and see if any get posted.  If
			 * an interrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;

			/* Flush any pending interrupts */
			wr32(E1000_ICR, ~0);

			wr32(E1000_IMC, ~mask);
			wr32(E1000_ICS, ~mask);
			wrfl();
			usleep_range(10000, 11000);

			if (adapter->test_icr & mask) {
				*data = 5;
				break;
			}
		}
	}

	/* Disable all the interrupts */
	wr32(E1000_IMC, ~0);
	wrfl();
	usleep_range(10000, 11000);

	/* Unhook test interrupt handler */
	if (adapter->flags & IGB_FLAG_HAS_MSIX)
		free_irq(adapter->msix_entries[0].vector, adapter);
	else
		free_irq(irq, adapter);

	return *data;
}