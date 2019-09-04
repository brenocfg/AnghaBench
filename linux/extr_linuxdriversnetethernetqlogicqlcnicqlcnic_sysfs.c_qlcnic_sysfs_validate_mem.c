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
struct qlcnic_adapter {int flags; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_DIAG_ENABLED ; 

__attribute__((used)) static int qlcnic_sysfs_validate_mem(struct qlcnic_adapter *adapter,
				     loff_t offset, size_t size)
{
	if (!(adapter->flags & QLCNIC_DIAG_ENABLED))
		return -EIO;

	if ((size != 8) || (offset & 0x7))
		return  -EIO;

	return 0;
}