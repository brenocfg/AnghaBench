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
typedef  char u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct cxl_afu {int crs_len; TYPE_1__* guest; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cxl_h_get_config (int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 char in_le16 (int /*<<< orphan*/ *) ; 
 char in_le32 (unsigned int*) ; 
 char in_le64 (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static int _guest_afu_cr_readXX(int sz, struct cxl_afu *afu, int cr_idx,
			u64 offset, u64 *val)
{
	unsigned long cr;
	char c;
	int rc = 0;

	if (afu->crs_len < sz)
		return -ENOENT;

	if (unlikely(offset >= afu->crs_len))
		return -ERANGE;

	cr = get_zeroed_page(GFP_KERNEL);
	if (!cr)
		return -ENOMEM;

	rc = cxl_h_get_config(afu->guest->handle, cr_idx, offset,
			virt_to_phys((void *)cr), sz);
	if (rc)
		goto err;

	switch (sz) {
	case 1:
		c = *((char *) cr);
		*val = c;
		break;
	case 2:
		*val = in_le16((u16 *)cr);
		break;
	case 4:
		*val = in_le32((unsigned *)cr);
		break;
	case 8:
		*val = in_le64((u64 *)cr);
		break;
	default:
		WARN_ON(1);
	}
err:
	free_page(cr);
	return rc;
}