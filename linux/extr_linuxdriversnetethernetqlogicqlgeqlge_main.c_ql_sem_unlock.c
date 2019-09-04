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
 int /*<<< orphan*/  SEM ; 
 int /*<<< orphan*/  ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ql_sem_unlock(struct ql_adapter *qdev, u32 sem_mask)
{
	ql_write32(qdev, SEM, sem_mask);
	ql_read32(qdev, SEM);	/* flush */
}