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
struct cryp_device_data {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_SR_BUSY_MASK ; 
 int CRYP_TEST_BITS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cryp_is_logic_busy(struct cryp_device_data *device_data)
{
	return CRYP_TEST_BITS(&device_data->base->sr,
			      CRYP_SR_BUSY_MASK);
}