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
typedef  int u32 ;
struct cxgbi_ppm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int cxgbi_ppm_sw_tag_is_usable(struct cxgbi_ppm *ppm,
					     u32 tag)
{
	/* the sw tag must be using <= 31 bits */
	return !(tag & 0x80000000U);
}