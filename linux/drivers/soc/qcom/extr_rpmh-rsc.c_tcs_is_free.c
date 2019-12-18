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
struct rsc_drv {int /*<<< orphan*/  tcs_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSC_DRV_STATUS ; 
 scalar_t__ read_tcs_reg (struct rsc_drv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tcs_is_free(struct rsc_drv *drv, int tcs_id)
{
	return !test_bit(tcs_id, drv->tcs_in_use) &&
	       read_tcs_reg(drv, RSC_DRV_STATUS, tcs_id, 0);
}