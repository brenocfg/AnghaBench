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
struct siw_mem {int /*<<< orphan*/  ref; } ;
struct siw_device {int /*<<< orphan*/  mem_xa; } ;

/* Variables and functions */
 scalar_t__ kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct siw_mem* xa_load (int /*<<< orphan*/ *,int) ; 

struct siw_mem *siw_mem_id2obj(struct siw_device *sdev, int stag_index)
{
	struct siw_mem *mem;

	rcu_read_lock();
	mem = xa_load(&sdev->mem_xa, stag_index);
	if (likely(mem && kref_get_unless_zero(&mem->ref))) {
		rcu_read_unlock();
		return mem;
	}
	rcu_read_unlock();

	return NULL;
}