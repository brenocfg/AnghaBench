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
struct ks8851_net {int rc_ccr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CCR_EEPROM ; 
 int EEPCR_EECS ; 
 int EEPCR_EESA ; 
 int ENOENT ; 
 int /*<<< orphan*/  KS_EEPCR ; 
 int /*<<< orphan*/  ks8851_wrreg16 (struct ks8851_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ks8851_eeprom_claim(struct ks8851_net *ks)
{
	if (!(ks->rc_ccr & CCR_EEPROM))
		return -ENOENT;

	mutex_lock(&ks->lock);

	/* start with clock low, cs high */
	ks8851_wrreg16(ks, KS_EEPCR, EEPCR_EESA | EEPCR_EECS);
	return 0;
}