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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 scalar_t__ PL_VF_WHOAMI_A ; 
 unsigned int SOURCEPF_G (int /*<<< orphan*/ ) ; 
 scalar_t__ T4VF_PL_BASE_ADDR ; 
 unsigned int T6_SOURCEPF_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,scalar_t__) ; 

unsigned int t4vf_get_pf_from_vf(struct adapter *adapter)
{
	u32 whoami;

	whoami = t4_read_reg(adapter, T4VF_PL_BASE_ADDR + PL_VF_WHOAMI_A);
	return (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5 ?
			SOURCEPF_G(whoami) : T6_SOURCEPF_G(whoami));
}