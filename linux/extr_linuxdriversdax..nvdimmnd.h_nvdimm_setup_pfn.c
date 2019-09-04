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
struct nd_pfn {int dummy; } ;
struct dev_pagemap {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static inline int nvdimm_setup_pfn(struct nd_pfn *nd_pfn,
				   struct dev_pagemap *pgmap)
{
	return -ENXIO;
}