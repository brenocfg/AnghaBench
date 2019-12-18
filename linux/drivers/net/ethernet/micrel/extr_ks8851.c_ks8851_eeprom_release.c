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
struct ks8851_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int EEPCR_EESA ; 
 int /*<<< orphan*/  KS_EEPCR ; 
 unsigned int ks8851_rdreg16 (struct ks8851_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8851_wrreg16 (struct ks8851_net*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ks8851_eeprom_release(struct ks8851_net *ks)
{
	unsigned val = ks8851_rdreg16(ks, KS_EEPCR);

	ks8851_wrreg16(ks, KS_EEPCR, val & ~EEPCR_EESA);
	mutex_unlock(&ks->lock);
}