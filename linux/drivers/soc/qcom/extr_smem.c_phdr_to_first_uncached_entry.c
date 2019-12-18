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
typedef  void smem_private_entry ;
struct smem_partition_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct smem_private_entry *
phdr_to_first_uncached_entry(struct smem_partition_header *phdr)
{
	void *p = phdr;

	return p + sizeof(*phdr);
}