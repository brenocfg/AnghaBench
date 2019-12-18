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
struct nand_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nanddev_bbt_cleanup (struct nand_device*) ; 
 scalar_t__ nanddev_bbt_is_initialized (struct nand_device*) ; 

void nanddev_cleanup(struct nand_device *nand)
{
	if (nanddev_bbt_is_initialized(nand))
		nanddev_bbt_cleanup(nand);
}