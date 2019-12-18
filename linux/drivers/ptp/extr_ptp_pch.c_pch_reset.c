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
struct pch_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pch_block_reset (struct pch_dev*) ; 
 int /*<<< orphan*/  pch_set_system_time_count (struct pch_dev*) ; 

__attribute__((used)) static void pch_reset(struct pch_dev *chip)
{
	/* Reset Hardware Assist */
	pch_block_reset(chip);

	/* enable all 32 bits in system time registers */
	pch_set_system_time_count(chip);
}