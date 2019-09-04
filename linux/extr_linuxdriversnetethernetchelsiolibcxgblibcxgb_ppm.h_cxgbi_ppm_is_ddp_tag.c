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
typedef  int u32 ;
struct TYPE_2__ {int no_ddp_mask; } ;
struct cxgbi_ppm {TYPE_1__ tformat; } ;

/* Variables and functions */

__attribute__((used)) static inline int cxgbi_ppm_is_ddp_tag(struct cxgbi_ppm *ppm, u32 tag)
{
	return !(tag & ppm->tformat.no_ddp_mask);
}