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
struct adapter {scalar_t__ slow_intr_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_INT_ENABLE0 ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t3_intr_disable(struct adapter *adapter)
{
	t3_write_reg(adapter, A_PL_INT_ENABLE0, 0);
	t3_read_reg(adapter, A_PL_INT_ENABLE0);	/* flush */
	adapter->slow_intr_mask = 0;
}