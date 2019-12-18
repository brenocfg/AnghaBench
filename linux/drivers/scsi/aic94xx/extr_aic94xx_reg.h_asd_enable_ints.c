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
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIMINTEN ; 
 int /*<<< orphan*/  COMSTATEN ; 
 int /*<<< orphan*/  DCHSTATUS ; 
 int EN_CFIFTOERR ; 
 int EN_CSBUFPERR ; 
 int EN_CSERR ; 
 int EN_OVLYERR ; 
 int SET_CHIMINTEN ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void asd_enable_ints(struct asd_ha_struct *asd_ha)
{
	/* Enable COM SAS interrupt on errors, COMSTAT */
	asd_write_reg_dword(asd_ha, COMSTATEN,
			    EN_CSBUFPERR | EN_CSERR | EN_OVLYERR);
	/* Enable DCH SAS CFIFTOERR */
	asd_write_reg_dword(asd_ha, DCHSTATUS, EN_CFIFTOERR);
	/* Enable Host Device interrupts */
	asd_write_reg_dword(asd_ha, CHIMINTEN, SET_CHIMINTEN);
}