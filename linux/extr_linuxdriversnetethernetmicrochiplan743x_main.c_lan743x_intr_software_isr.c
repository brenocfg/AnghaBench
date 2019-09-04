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
typedef  int u32 ;
struct lan743x_intr {int software_isr_flag; } ;
struct lan743x_adapter {struct lan743x_intr intr; } ;

/* Variables and functions */
 int INT_BIT_SW_GP_ ; 
 int /*<<< orphan*/  INT_STS ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan743x_intr_software_isr(void *context)
{
	struct lan743x_adapter *adapter = context;
	struct lan743x_intr *intr = &adapter->intr;
	u32 int_sts;

	int_sts = lan743x_csr_read(adapter, INT_STS);
	if (int_sts & INT_BIT_SW_GP_) {
		lan743x_csr_write(adapter, INT_STS, INT_BIT_SW_GP_);
		intr->software_isr_flag = 1;
	}
}