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
struct TYPE_3__ {int /*<<< orphan*/  subsample; } ;
struct TYPE_4__ {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_HIC_STATUS ; 
 int /*<<< orphan*/  MCHIP_HIC_STATUS_IDLE ; 
 int /*<<< orphan*/  MCHIP_MCC_B_XRANGE ; 
 int /*<<< orphan*/  MCHIP_MCC_B_YRANGE ; 
 int /*<<< orphan*/  MCHIP_MCC_R_SAMPLING ; 
 int /*<<< orphan*/  MCHIP_MCC_R_XRANGE ; 
 int /*<<< orphan*/  MCHIP_MCC_R_YRANGE ; 
 int /*<<< orphan*/  mchip_delay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_hsize () ; 
 int /*<<< orphan*/  mchip_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_vsize () ; 
 TYPE_2__ meye ; 

__attribute__((used)) static void mchip_subsample(void)
{
	mchip_set(MCHIP_MCC_R_SAMPLING, meye.params.subsample);
	mchip_set(MCHIP_MCC_R_XRANGE, mchip_hsize());
	mchip_set(MCHIP_MCC_R_YRANGE, mchip_vsize());
	mchip_set(MCHIP_MCC_B_XRANGE, mchip_hsize());
	mchip_set(MCHIP_MCC_B_YRANGE, mchip_vsize());
	mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE);
}