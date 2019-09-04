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
struct kfd_process_device {int lds_base; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int get_sh_mem_bases_32(struct kfd_process_device *pdd)
{
	return (pdd->lds_base >> 16) & 0xFF;
}