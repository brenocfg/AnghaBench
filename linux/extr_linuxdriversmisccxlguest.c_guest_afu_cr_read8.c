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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int _guest_afu_cr_readXX (int,struct cxl_afu*,int,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int guest_afu_cr_read8(struct cxl_afu *afu, int cr_idx, u64 offset,
			u8 *out)
{
	int rc;
	u64 val;

	rc = _guest_afu_cr_readXX(1, afu, cr_idx, offset, &val);
	if (!rc)
		*out = (u8) val;
	return rc;
}