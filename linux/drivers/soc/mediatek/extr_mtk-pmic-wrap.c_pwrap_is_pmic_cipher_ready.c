#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pmic_wrapper {TYPE_1__* slave; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dew_regs; } ;

/* Variables and functions */
 size_t PWRAP_DEW_CIPHER_RDY ; 
 int pwrap_read (struct pmic_wrapper*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool pwrap_is_pmic_cipher_ready(struct pmic_wrapper *wrp)
{
	u32 rdata;
	int ret;

	ret = pwrap_read(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_RDY],
			 &rdata);
	if (ret)
		return false;

	return rdata == 1;
}