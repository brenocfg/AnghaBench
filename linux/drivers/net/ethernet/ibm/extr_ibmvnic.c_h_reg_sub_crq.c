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

/* Variables and functions */
 int /*<<< orphan*/  H_REG_SUB_CRQ ; 
 int PLPAR_HCALL_BUFSIZE ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static long h_reg_sub_crq(unsigned long unit_address, unsigned long token,
			  unsigned long length, unsigned long *number,
			  unsigned long *irq)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	rc = plpar_hcall(H_REG_SUB_CRQ, retbuf, unit_address, token, length);
	*number = retbuf[0];
	*irq = retbuf[1];

	return rc;
}