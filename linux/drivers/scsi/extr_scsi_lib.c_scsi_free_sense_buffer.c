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

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  scsi_select_sense_cache (int) ; 

__attribute__((used)) static void scsi_free_sense_buffer(bool unchecked_isa_dma,
				   unsigned char *sense_buffer)
{
	kmem_cache_free(scsi_select_sense_cache(unchecked_isa_dma),
			sense_buffer);
}