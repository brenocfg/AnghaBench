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
typedef  int u64 ;
typedef  int u32 ;
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int native_afu_cr_read32 (struct cxl_afu*,int,int,int*) ; 

__attribute__((used)) static int native_afu_cr_read8(struct cxl_afu *afu, int cr, u64 off, u8 *out)
{
	u64 aligned_off = off & ~0x3L;
	u32 val;
	int rc;

	rc = native_afu_cr_read32(afu, cr, aligned_off, &val);
	if (!rc)
		*out = (val >> ((off & 0x3) * 8)) & 0xff;
	return rc;
}