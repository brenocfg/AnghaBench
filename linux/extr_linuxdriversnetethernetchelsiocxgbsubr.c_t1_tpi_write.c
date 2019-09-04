#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tpi_lock; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int __t1_tpi_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int t1_tpi_write(adapter_t *adapter, u32 addr, u32 value)
{
	int ret;

	spin_lock(&adapter->tpi_lock);
	ret = __t1_tpi_write(adapter, addr, value);
	spin_unlock(&adapter->tpi_lock);
	return ret;
}