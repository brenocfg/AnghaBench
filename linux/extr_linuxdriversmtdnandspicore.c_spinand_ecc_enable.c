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
struct spinand_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_ECC_ENABLE ; 
 int spinand_upd_cfg (struct spinand_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spinand_ecc_enable(struct spinand_device *spinand,
			      bool enable)
{
	return spinand_upd_cfg(spinand, CFG_ECC_ENABLE,
			       enable ? CFG_ECC_ENABLE : 0);
}