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
struct mei_txe_hw {int intr_cause; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TXE_INTR_ALIVENESS ; 
 int TXE_INTR_IN_READY ; 
 int TXE_INTR_OUT_DB ; 
 int TXE_INTR_READINESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static bool mei_txe_pending_interrupts(struct mei_device *dev)
{

	struct mei_txe_hw *hw = to_txe_hw(dev);
	bool ret = (hw->intr_cause & (TXE_INTR_READINESS |
				      TXE_INTR_ALIVENESS |
				      TXE_INTR_IN_READY  |
				      TXE_INTR_OUT_DB));

	if (ret) {
		dev_dbg(dev->dev,
			"Pending Interrupts InReady=%01d Readiness=%01d, Aliveness=%01d, OutDoor=%01d\n",
			!!(hw->intr_cause & TXE_INTR_IN_READY),
			!!(hw->intr_cause & TXE_INTR_READINESS),
			!!(hw->intr_cause & TXE_INTR_ALIVENESS),
			!!(hw->intr_cause & TXE_INTR_OUT_DB));
	}
	return ret;
}