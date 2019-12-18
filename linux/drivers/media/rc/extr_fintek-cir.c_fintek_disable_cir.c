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
struct fintek_dev {int /*<<< orphan*/  logical_dev_cir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_CR_DEV_EN ; 
 int /*<<< orphan*/  LOGICAL_DEV_DISABLE ; 
 int /*<<< orphan*/  fintek_config_mode_disable (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_config_mode_enable (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_cr_write (struct fintek_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fintek_select_logical_dev (struct fintek_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fintek_disable_cir(struct fintek_dev *fintek)
{
	fintek_config_mode_enable(fintek);

	/* disable the CIR logical device */
	fintek_select_logical_dev(fintek, fintek->logical_dev_cir);
	fintek_cr_write(fintek, LOGICAL_DEV_DISABLE, CIR_CR_DEV_EN);

	fintek_config_mode_disable(fintek);
}