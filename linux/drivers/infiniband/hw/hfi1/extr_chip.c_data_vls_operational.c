#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct hfi1_pportdata {int vls_supported; TYPE_2__* dd; int /*<<< orphan*/  actual_vls_operational; } ;
struct TYPE_4__ {TYPE_1__* vld; } ;
struct TYPE_3__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ SEND_CM_CREDIT_VL ; 
 scalar_t__ read_csr (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static inline bool data_vls_operational(struct hfi1_pportdata *ppd)
{
	int i;
	u64 reg;

	if (!ppd->actual_vls_operational)
		return false;

	for (i = 0; i < ppd->vls_supported; i++) {
		reg = read_csr(ppd->dd, SEND_CM_CREDIT_VL + (8 * i));
		if ((reg && !ppd->dd->vld[i].mtu) ||
		    (!reg && ppd->dd->vld[i].mtu))
			return false;
	}

	return true;
}