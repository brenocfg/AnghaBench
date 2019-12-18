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
typedef  int u64 ;
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int test_icr; struct e1000_hw hw; TYPE_1__* pdev; struct net_device* netdev; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  ICS ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  IMS ; 
 int /*<<< orphan*/  IRQF_PROBE_SHARED ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  e1000_test_intr ; 
 int /*<<< orphan*/  e_info (struct e1000_hw*,char*,char*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int,struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int e1000_intr_test(struct e1000_adapter *adapter, u64 *data)
{
	struct net_device *netdev = adapter->netdev;
	u32 mask, i = 0;
	bool shared_int = true;
	u32 irq = adapter->pdev->irq;
	struct e1000_hw *hw = &adapter->hw;

	*data = 0;

	/* NOTE: we don't test MSI interrupts here, yet
	 * Hook up test interrupt handler just for this test
	 */
	if (!request_irq(irq, e1000_test_intr, IRQF_PROBE_SHARED, netdev->name,
			 netdev))
		shared_int = false;
	else if (request_irq(irq, e1000_test_intr, IRQF_SHARED,
			     netdev->name, netdev)) {
		*data = 1;
		return -1;
	}
	e_info(hw, "testing %s interrupt\n", (shared_int ?
	       "shared" : "unshared"));

	/* Disable all the interrupts */
	ew32(IMC, 0xFFFFFFFF);
	E1000_WRITE_FLUSH();
	msleep(10);

	/* Test each interrupt */
	for (; i < 10; i++) {
		/* Interrupt to test */
		mask = 1 << i;

		if (!shared_int) {
			/* Disable the interrupt to be reported in
			 * the cause register and then force the same
			 * interrupt and see if one gets posted.  If
			 * an interrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;
			ew32(IMC, mask);
			ew32(ICS, mask);
			E1000_WRITE_FLUSH();
			msleep(10);

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
		ew32(IMS, mask);
		ew32(ICS, mask);
		E1000_WRITE_FLUSH();
		msleep(10);

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
			ew32(IMC, ~mask & 0x00007FFF);
			ew32(ICS, ~mask & 0x00007FFF);
			E1000_WRITE_FLUSH();
			msleep(10);

			if (adapter->test_icr) {
				*data = 5;
				break;
			}
		}
	}

	/* Disable all the interrupts */
	ew32(IMC, 0xFFFFFFFF);
	E1000_WRITE_FLUSH();
	msleep(10);

	/* Unhook test interrupt handler */
	free_irq(irq, netdev);

	return *data;
}