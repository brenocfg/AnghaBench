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
struct atmel_nand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_nand_controller_cleanup (struct atmel_nand_controller*) ; 
 int atmel_nand_controller_remove_nands (struct atmel_nand_controller*) ; 

__attribute__((used)) static int
atmel_smc_nand_controller_remove(struct atmel_nand_controller *nc)
{
	int ret;

	ret = atmel_nand_controller_remove_nands(nc);
	if (ret)
		return ret;

	atmel_nand_controller_cleanup(nc);

	return 0;
}