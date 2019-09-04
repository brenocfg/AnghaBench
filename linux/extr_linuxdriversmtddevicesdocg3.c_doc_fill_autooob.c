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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 size_t DOC_LAYOUT_OOB_PAGEINFO_SZ ; 
 size_t DOC_LAYOUT_OOB_UNUSED_OFS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void doc_fill_autooob(u8 *dst, u8 *oobsrc)
{
	memcpy(dst, oobsrc, DOC_LAYOUT_OOB_PAGEINFO_SZ);
	dst[DOC_LAYOUT_OOB_UNUSED_OFS] = oobsrc[DOC_LAYOUT_OOB_PAGEINFO_SZ];
}