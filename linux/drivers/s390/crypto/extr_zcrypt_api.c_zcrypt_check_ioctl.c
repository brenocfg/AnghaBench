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
struct ap_perms {int /*<<< orphan*/  ioctlm; } ;

/* Variables and functions */
 int AP_IOCTLS ; 
 int /*<<< orphan*/  DBF_WARN ; 
 int EPERM ; 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int,int) ; 
 unsigned int _IOC_NRMASK ; 
 unsigned int _IOC_NRSHIFT ; 
 scalar_t__ test_bit_inv (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int zcrypt_check_ioctl(struct ap_perms *perms,
				     unsigned int cmd)
{
	int rc = -EPERM;
	int ioctlnr = (cmd & _IOC_NRMASK) >> _IOC_NRSHIFT;

	if (ioctlnr > 0 && ioctlnr < AP_IOCTLS) {
		if (test_bit_inv(ioctlnr, perms->ioctlm))
			rc = 0;
	}

	if (rc)
		ZCRYPT_DBF(DBF_WARN,
			   "ioctl check failed: ioctlnr=0x%04x rc=%d\n",
			   ioctlnr, rc);

	return rc;
}