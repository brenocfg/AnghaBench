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
struct TYPE_2__ {int resend; scalar_t__ bmi; scalar_t__ efl; scalar_t__ lbc; scalar_t__ pem; scalar_t__ pom; scalar_t__ nps_pkt; scalar_t__ nps_core; } ;
union nps_core_int_active {int /*<<< orphan*/  value; TYPE_1__ s; } ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_CORE_INT_ACTIVE ; 
 int /*<<< orphan*/  clear_bmi_err_intr (struct nitrox_device*) ; 
 int /*<<< orphan*/  clear_efl_err_intr (struct nitrox_device*) ; 
 int /*<<< orphan*/  clear_lbc_err_intr (struct nitrox_device*) ; 
 int /*<<< orphan*/  clear_nps_core_err_intr (struct nitrox_device*) ; 
 int /*<<< orphan*/  clear_nps_pkt_err_intr (struct nitrox_device*) ; 
 int /*<<< orphan*/  clear_pem_err_intr (struct nitrox_device*) ; 
 int /*<<< orphan*/  clear_pom_err_intr (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_nps_core_int_active(struct nitrox_device *ndev)
{
	union nps_core_int_active core_int_active;

	core_int_active.value = nitrox_read_csr(ndev, NPS_CORE_INT_ACTIVE);

	if (core_int_active.s.nps_core)
		clear_nps_core_err_intr(ndev);

	if (core_int_active.s.nps_pkt)
		clear_nps_pkt_err_intr(ndev);

	if (core_int_active.s.pom)
		clear_pom_err_intr(ndev);

	if (core_int_active.s.pem)
		clear_pem_err_intr(ndev);

	if (core_int_active.s.lbc)
		clear_lbc_err_intr(ndev);

	if (core_int_active.s.efl)
		clear_efl_err_intr(ndev);

	if (core_int_active.s.bmi)
		clear_bmi_err_intr(ndev);

	/* If more work callback the ISR, set resend */
	core_int_active.s.resend = 1;
	nitrox_write_csr(ndev, NPS_CORE_INT_ACTIVE, core_int_active.value);
}