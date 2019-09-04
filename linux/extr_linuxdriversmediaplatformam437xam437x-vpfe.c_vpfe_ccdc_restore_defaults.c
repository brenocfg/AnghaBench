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
struct vpfe_ccdc {int dummy; } ;

/* Variables and functions */
 int VPFE_ALAW ; 
 int /*<<< orphan*/  VPFE_CCDC_GAMMA_BITS_11_2 ; 
 int VPFE_CULLING ; 
 int /*<<< orphan*/  VPFE_NO_CULLING ; 
 int /*<<< orphan*/  vpfe_pcr_enable (struct vpfe_ccdc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_reg_write (struct vpfe_ccdc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vpfe_ccdc_restore_defaults(struct vpfe_ccdc *ccdc)
{
	int i;

	/* Disable CCDC */
	vpfe_pcr_enable(ccdc, 0);

	/* set all registers to default value */
	for (i = 4; i <= 0x94; i += 4)
		vpfe_reg_write(ccdc, 0,  i);

	vpfe_reg_write(ccdc, VPFE_NO_CULLING, VPFE_CULLING);
	vpfe_reg_write(ccdc, VPFE_CCDC_GAMMA_BITS_11_2, VPFE_ALAW);
}