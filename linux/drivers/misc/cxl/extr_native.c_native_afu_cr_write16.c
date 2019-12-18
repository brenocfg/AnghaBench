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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int native_afu_cr_read32 (struct cxl_afu*,int,int,int*) ; 
 int native_afu_cr_write32 (struct cxl_afu*,int,int,int) ; 

__attribute__((used)) static int native_afu_cr_write16(struct cxl_afu *afu, int cr, u64 off, u16 in)
{
	u64 aligned_off = off & ~0x3L;
	u32 val32, mask, shift;
	int rc;

	rc = native_afu_cr_read32(afu, cr, aligned_off, &val32);
	if (rc)
		return rc;
	shift = (off & 0x3) * 8;
	WARN_ON(shift == 24);
	mask = 0xffff << shift;
	val32 = (val32 & ~mask) | (in << shift);

	rc = native_afu_cr_write32(afu, cr, aligned_off, val32);
	return rc;
}