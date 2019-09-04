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
struct TYPE_2__ {int ent_en; int rng_en; } ;
union efl_rnm_ctl_status {int /*<<< orphan*/  value; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFL_RNM_CTL_STATUS ; 
 int /*<<< orphan*/  nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nitrox_config_rand_unit(struct nitrox_device *ndev)
{
	union efl_rnm_ctl_status efl_rnm_ctl;
	u64 offset;

	offset = EFL_RNM_CTL_STATUS;
	efl_rnm_ctl.value = nitrox_read_csr(ndev, offset);
	efl_rnm_ctl.s.ent_en = 1;
	efl_rnm_ctl.s.rng_en = 1;
	nitrox_write_csr(ndev, offset, efl_rnm_ctl.value);
}