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
struct ql_adapter {int func; int alt_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  STS ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 

int ql_own_firmware(struct ql_adapter *qdev)
{
	u32 temp;

	/* If we are the lower of the 2 NIC functions
	 * on the chip the we are responsible for
	 * core dump and firmware reset after an error.
	 */
	if (qdev->func < qdev->alt_func)
		return 1;

	/* If we are the higher of the 2 NIC functions
	 * on the chip and the lower function is not
	 * enabled, then we are responsible for
	 * core dump and firmware reset after an error.
	 */
	temp =  ql_read32(qdev, STS);
	if (!(temp & (1 << (8 + qdev->alt_func))))
		return 1;

	return 0;

}