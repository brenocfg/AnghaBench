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
typedef  int /*<<< orphan*/  u32 ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNA_ETS ; 
 int /*<<< orphan*/  NIC_ETS ; 
 int /*<<< orphan*/  ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_get_ets_regs(struct ql_adapter *qdev, u32 *buf)
{
	int status = 0;
	int i;

	for (i = 0; i < 8; i++, buf++) {
		ql_write32(qdev, NIC_ETS, i << 29 | 0x08000000);
		*buf = ql_read32(qdev, NIC_ETS);
	}

	for (i = 0; i < 2; i++, buf++) {
		ql_write32(qdev, CNA_ETS, i << 29 | 0x08000000);
		*buf = ql_read32(qdev, CNA_ETS);
	}

	return status;
}