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
typedef  scalar_t__ uint32_t ;
struct vsoc_device_region {scalar_t__ region_begin_offset; scalar_t__ region_end_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t vsoc_device_region_size(struct vsoc_device_region *r)
{
	return r->region_end_offset - r->region_begin_offset;
}