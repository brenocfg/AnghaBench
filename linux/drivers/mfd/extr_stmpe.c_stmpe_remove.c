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
struct stmpe {int /*<<< orphan*/  dev; int /*<<< orphan*/  vcc; int /*<<< orphan*/  vio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMPE_BLOCK_ADC ; 
 int /*<<< orphan*/  __stmpe_disable (struct stmpe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

int stmpe_remove(struct stmpe *stmpe)
{
	if (!IS_ERR(stmpe->vio))
		regulator_disable(stmpe->vio);
	if (!IS_ERR(stmpe->vcc))
		regulator_disable(stmpe->vcc);

	__stmpe_disable(stmpe, STMPE_BLOCK_ADC);

	mfd_remove_devices(stmpe->dev);

	return 0;
}