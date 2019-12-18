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
struct ks8851_net {int dummy; } ;
struct eeprom_93cx6 {scalar_t__ reg_chip_select; scalar_t__ reg_data_clock; scalar_t__ reg_data_in; scalar_t__ drive_data; struct ks8851_net* data; } ;

/* Variables and functions */
 unsigned int EEPCR_EECS ; 
 unsigned int EEPCR_EEDO ; 
 unsigned int EEPCR_EESA ; 
 unsigned int EEPCR_EESCK ; 
 unsigned int EEPCR_EESRWA ; 
 int /*<<< orphan*/  KS_EEPCR ; 
 int /*<<< orphan*/  ks8851_wrreg16 (struct ks8851_net*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ks8851_eeprom_regwrite(struct eeprom_93cx6 *ee)
{
	struct ks8851_net *ks = ee->data;
	unsigned val = EEPCR_EESA;	/* default - eeprom access on */

	if (ee->drive_data)
		val |= EEPCR_EESRWA;
	if (ee->reg_data_in)
		val |= EEPCR_EEDO;
	if (ee->reg_data_clock)
		val |= EEPCR_EESCK;
	if (ee->reg_chip_select)
		val |= EEPCR_EECS;

	ks8851_wrreg16(ks, KS_EEPCR, val);
}