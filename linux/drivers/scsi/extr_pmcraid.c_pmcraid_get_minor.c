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

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_MAX_ADAPTERS ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_minor ; 

__attribute__((used)) static unsigned short pmcraid_get_minor(void)
{
	int minor;

	minor = find_first_zero_bit(pmcraid_minor, PMCRAID_MAX_ADAPTERS);
	__set_bit(minor, pmcraid_minor);
	return minor;
}