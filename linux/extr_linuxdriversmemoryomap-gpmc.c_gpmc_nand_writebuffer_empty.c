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
 int /*<<< orphan*/  GPMC_STATUS ; 
 int GPMC_STATUS_EMPTYWRITEBUFFERSTATUS ; 
 int gpmc_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gpmc_nand_writebuffer_empty(void)
{
	if (gpmc_read_reg(GPMC_STATUS) & GPMC_STATUS_EMPTYWRITEBUFFERSTATUS)
		return true;

	return false;
}