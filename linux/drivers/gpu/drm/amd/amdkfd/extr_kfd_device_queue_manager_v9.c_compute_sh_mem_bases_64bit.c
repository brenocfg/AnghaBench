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
typedef  int uint32_t ;
struct kfd_process_device {int lds_base; int scratch_base; } ;

/* Variables and functions */
 int SH_MEM_BASES__SHARED_BASE__SHIFT ; 

__attribute__((used)) static uint32_t compute_sh_mem_bases_64bit(struct kfd_process_device *pdd)
{
	uint32_t shared_base = pdd->lds_base >> 48;
	uint32_t private_base = pdd->scratch_base >> 48;

	return (shared_base << SH_MEM_BASES__SHARED_BASE__SHIFT) |
		private_base;
}