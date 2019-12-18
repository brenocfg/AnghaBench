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
struct hl_eq {scalar_t__ kernel_address; scalar_t__ ci; } ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HL_EQ_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hl_eq_reset(struct hl_device *hdev, struct hl_eq *q)
{
	q->ci = 0;

	/*
	 * It's not enough to just reset the PI/CI because the H/W may have
	 * written valid completion entries before it was halted and therefore
	 * we need to clean the actual queues so we won't process old entries
	 * when the device is operational again
	 */

	memset((void *) (uintptr_t) q->kernel_address, 0, HL_EQ_SIZE_IN_BYTES);
}