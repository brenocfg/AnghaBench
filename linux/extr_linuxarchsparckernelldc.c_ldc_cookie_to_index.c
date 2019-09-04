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
typedef  unsigned long long u64 ;

/* Variables and functions */
 unsigned long long COOKIE_PGSZ_CODE ; 
 unsigned long long COOKIE_PGSZ_CODE_SHIFT ; 

__attribute__((used)) static unsigned long ldc_cookie_to_index(u64 cookie, void *arg)
{
	u64 szcode = cookie >> COOKIE_PGSZ_CODE_SHIFT;
	/* struct ldc_iommu *ldc_iommu = (struct ldc_iommu *)arg; */

	cookie &= ~COOKIE_PGSZ_CODE;

	return (cookie >> (13ULL + (szcode * 3ULL)));
}