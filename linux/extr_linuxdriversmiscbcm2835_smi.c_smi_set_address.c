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
struct bcm2835_smi_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BIT_FIELD (int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SMIA ; 
 int /*<<< orphan*/  SMIA_ADDR ; 
 int /*<<< orphan*/  SMIDA ; 
 int /*<<< orphan*/  SMIDA_ADDR ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smi_set_address(struct bcm2835_smi_instance *inst,
	unsigned int address)
{
	int smia_temp = 0, smida_temp = 0;

	SET_BIT_FIELD(smia_temp, SMIA_ADDR, address);
	SET_BIT_FIELD(smida_temp, SMIDA_ADDR, address);

	/* Write to both address registers - user doesn't care whether we're
	   doing programmed or direct transfers. */
	write_smi_reg(inst, smia_temp, SMIA);
	write_smi_reg(inst, smida_temp, SMIDA);
}