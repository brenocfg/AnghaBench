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
typedef  scalar_t__ u32 ;
struct etnaviv_vram_mapping {scalar_t__ iova; } ;
struct etnaviv_cmdbuf {scalar_t__ suballoc_offset; } ;

/* Variables and functions */

u32 etnaviv_cmdbuf_get_va(struct etnaviv_cmdbuf *buf,
			  struct etnaviv_vram_mapping *mapping)
{
	return mapping->iova + buf->suballoc_offset;
}