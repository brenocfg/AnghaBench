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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned char* kmem_cache_alloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_select_sense_cache (int) ; 

__attribute__((used)) static unsigned char *scsi_alloc_sense_buffer(bool unchecked_isa_dma,
	gfp_t gfp_mask, int numa_node)
{
	return kmem_cache_alloc_node(scsi_select_sense_cache(unchecked_isa_dma),
				     gfp_mask, numa_node);
}