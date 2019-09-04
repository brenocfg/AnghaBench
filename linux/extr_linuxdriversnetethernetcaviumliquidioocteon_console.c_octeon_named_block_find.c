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
typedef  int /*<<< orphan*/  u64 ;
struct octeon_device {int dummy; } ;
struct cvmx_bootmem_named_block_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 struct cvmx_bootmem_named_block_desc* __cvmx_bootmem_find_named_block_flags (struct octeon_device*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_remote_lock () ; 
 int /*<<< orphan*/  octeon_remote_unlock () ; 

__attribute__((used)) static int octeon_named_block_find(struct octeon_device *oct, const char *name,
				   u64 *base_addr, u64 *size)
{
	const struct cvmx_bootmem_named_block_desc *named_block;

	octeon_remote_lock();
	named_block = __cvmx_bootmem_find_named_block_flags(oct, name, 0);
	octeon_remote_unlock();
	if (named_block) {
		*base_addr = named_block->base_addr;
		*size = named_block->size;
		return 0;
	}
	return 1;
}