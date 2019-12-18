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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int hfi1_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_CFG_MUTEX ; 
 int /*<<< orphan*/  dd_dev_warn (struct hfi1_devdata*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void release_hw_mutex(struct hfi1_devdata *dd)
{
	u8 mask = 1 << dd->hfi1_id;
	u8 user = (u8)read_csr(dd, ASIC_CFG_MUTEX);

	if (user != mask)
		dd_dev_warn(dd,
			    "Unable to release hardware mutex, mutex mask %u, my mask %u\n",
			    (u32)user, (u32)mask);
	else
		write_csr(dd, ASIC_CFG_MUTEX, 0);
}