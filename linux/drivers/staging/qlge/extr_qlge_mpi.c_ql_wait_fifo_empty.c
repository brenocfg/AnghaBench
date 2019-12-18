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
typedef  int u32 ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MB_GET_MPI_TFK_FIFO_EMPTY ; 
 int /*<<< orphan*/  STS ; 
 int STS_NFE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ql_mb_get_mgmnt_traffic_ctl (struct ql_adapter*,int*) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 

int ql_wait_fifo_empty(struct ql_adapter *qdev)
{
	int count = 5;
	u32 mgmnt_fifo_empty;
	u32 nic_fifo_empty;

	do {
		nic_fifo_empty = ql_read32(qdev, STS) & STS_NFE;
		ql_mb_get_mgmnt_traffic_ctl(qdev, &mgmnt_fifo_empty);
		mgmnt_fifo_empty &= MB_GET_MPI_TFK_FIFO_EMPTY;
		if (nic_fifo_empty && mgmnt_fifo_empty)
			return 0;
		msleep(100);
	} while (count-- > 0);
	return -ETIMEDOUT;
}