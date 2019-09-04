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
struct atl2_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL2_WRITE_FLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMR_NORMAL_MASK ; 
 int /*<<< orphan*/  REG_IMR ; 

__attribute__((used)) static inline void atl2_irq_enable(struct atl2_adapter *adapter)
{
	ATL2_WRITE_REG(&adapter->hw, REG_IMR, IMR_NORMAL_MASK);
	ATL2_WRITE_FLUSH(&adapter->hw);
}