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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_INT_CAUSE_A ; 
 int /*<<< orphan*/  MA_INT_WRAP_STATUS_A ; 
 int /*<<< orphan*/  MA_PARITY_ERROR_STATUS1_A ; 
 int /*<<< orphan*/  MA_PARITY_ERROR_STATUS2_A ; 
 int MEM_PERR_INT_CAUSE_F ; 
 int MEM_WRAP_ADDRESS_G (int) ; 
 int /*<<< orphan*/  MEM_WRAP_CLIENT_NUM_G (int) ; 
 int MEM_WRAP_INT_CAUSE_F ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ma_intr_handler(struct adapter *adap)
{
	u32 v, status = t4_read_reg(adap, MA_INT_CAUSE_A);

	if (status & MEM_PERR_INT_CAUSE_F) {
		dev_alert(adap->pdev_dev,
			  "MA parity error, parity status %#x\n",
			  t4_read_reg(adap, MA_PARITY_ERROR_STATUS1_A));
		if (is_t5(adap->params.chip))
			dev_alert(adap->pdev_dev,
				  "MA parity error, parity status %#x\n",
				  t4_read_reg(adap,
					      MA_PARITY_ERROR_STATUS2_A));
	}
	if (status & MEM_WRAP_INT_CAUSE_F) {
		v = t4_read_reg(adap, MA_INT_WRAP_STATUS_A);
		dev_alert(adap->pdev_dev, "MA address wrap-around error by "
			  "client %u to address %#x\n",
			  MEM_WRAP_CLIENT_NUM_G(v),
			  MEM_WRAP_ADDRESS_G(v) << 4);
	}
	t4_write_reg(adap, MA_INT_CAUSE_A, status);
	t4_fatal_err(adap);
}