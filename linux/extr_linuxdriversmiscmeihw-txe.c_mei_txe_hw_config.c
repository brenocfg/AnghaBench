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
struct mei_txe_hw {int /*<<< orphan*/  readiness; int /*<<< orphan*/  aliveness; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_txe_aliveness_get (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_readiness_get (struct mei_device*) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static void mei_txe_hw_config(struct mei_device *dev)
{

	struct mei_txe_hw *hw = to_txe_hw(dev);

	hw->aliveness = mei_txe_aliveness_get(dev);
	hw->readiness = mei_txe_readiness_get(dev);

	dev_dbg(dev->dev, "aliveness_resp = 0x%08x, readiness = 0x%08x.\n",
		hw->aliveness, hw->readiness);
}