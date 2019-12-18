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
struct phy_device {int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 unsigned int phy_speeds (unsigned int*,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int phy_supported_speeds(struct phy_device *phy,
				  unsigned int *speeds,
				  unsigned int size)
{
	return phy_speeds(speeds, size, phy->supported);
}