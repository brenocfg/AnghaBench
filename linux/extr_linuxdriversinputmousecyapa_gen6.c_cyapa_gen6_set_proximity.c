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
struct cyapa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_DISABLE_CMD_IRQ ; 
 int /*<<< orphan*/  GEN6_ENABLE_CMD_IRQ ; 
 int /*<<< orphan*/  cyapa_gen6_config_dev_irq (struct cyapa*,int /*<<< orphan*/ ) ; 
 int cyapa_pip_set_proximity (struct cyapa*,int) ; 

__attribute__((used)) static int cyapa_gen6_set_proximity(struct cyapa *cyapa, bool enable)
{
	int error;

	cyapa_gen6_config_dev_irq(cyapa, GEN6_DISABLE_CMD_IRQ);
	error = cyapa_pip_set_proximity(cyapa, enable);
	cyapa_gen6_config_dev_irq(cyapa, GEN6_ENABLE_CMD_IRQ);

	return error;
}