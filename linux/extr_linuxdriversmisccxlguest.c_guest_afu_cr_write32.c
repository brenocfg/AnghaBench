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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int EPERM ; 

__attribute__((used)) static int guest_afu_cr_write32(struct cxl_afu *afu, int cr, u64 off, u32 in)
{
	/* config record is not writable from guest */
	return -EPERM;
}