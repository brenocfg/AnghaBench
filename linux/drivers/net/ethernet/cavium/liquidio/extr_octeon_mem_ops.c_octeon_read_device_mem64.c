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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct octeon_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  __octeon_pci_rw_core_mem (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 

u64 octeon_read_device_mem64(struct octeon_device *oct, u64 coreaddr)
{
	__be64 ret;

	__octeon_pci_rw_core_mem(oct, coreaddr, (u8 *)&ret, 8, 1);

	return be64_to_cpu(ret);
}