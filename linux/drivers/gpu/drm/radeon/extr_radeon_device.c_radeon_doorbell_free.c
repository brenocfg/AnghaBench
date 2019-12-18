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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ num_doorbells; int /*<<< orphan*/  used; } ;
struct radeon_device {TYPE_1__ doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

void radeon_doorbell_free(struct radeon_device *rdev, u32 doorbell)
{
	if (doorbell < rdev->doorbell.num_doorbells)
		__clear_bit(doorbell, rdev->doorbell.used);
}