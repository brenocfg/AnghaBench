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
typedef  int u8 ;
struct cfi_private {struct cfi_pri_amdstd* cmdset_priv; } ;
struct cfi_pri_amdstd {char MinorVersion; int SoftwareFeatures; } ;

/* Variables and functions */
 int CFI_POLL_DQ ; 
 int CFI_POLL_STATUS_REG ; 

__attribute__((used)) static int cfi_use_status_reg(struct cfi_private *cfi)
{
	struct cfi_pri_amdstd *extp = cfi->cmdset_priv;
	u8 poll_mask = CFI_POLL_STATUS_REG | CFI_POLL_DQ;

	return extp->MinorVersion >= '5' &&
		(extp->SoftwareFeatures & poll_mask) == CFI_POLL_STATUS_REG;
}