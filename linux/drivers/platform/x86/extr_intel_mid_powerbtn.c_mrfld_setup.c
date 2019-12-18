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
struct mid_pb_ddata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCOVE_PBIRQ ; 
 int /*<<< orphan*/  BCOVE_PBIRQMASK ; 
 int /*<<< orphan*/  MSIC_PWRBTNM ; 
 int /*<<< orphan*/  intel_scu_ipc_update_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrfld_setup(struct mid_pb_ddata *ddata)
{
	/* Unmask the PBIRQ and MPBIRQ on Tangier */
	intel_scu_ipc_update_register(BCOVE_PBIRQ, 0, MSIC_PWRBTNM);
	intel_scu_ipc_update_register(BCOVE_PBIRQMASK, 0, MSIC_PWRBTNM);

	return 0;
}