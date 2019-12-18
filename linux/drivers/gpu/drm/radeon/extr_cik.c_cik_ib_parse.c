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
struct radeon_ib {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */

int cik_ib_parse(struct radeon_device *rdev, struct radeon_ib *ib)
{
	return 0;
}