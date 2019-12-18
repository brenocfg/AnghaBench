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
typedef  int /*<<< orphan*/  u32 ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ql_sem_trylock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ql_sem_spinlock(struct ql_adapter *qdev, u32 sem_mask)
{
	unsigned int wait_count = 30;
	do {
		if (!ql_sem_trylock(qdev, sem_mask))
			return 0;
		udelay(100);
	} while (--wait_count);
	return -ETIMEDOUT;
}