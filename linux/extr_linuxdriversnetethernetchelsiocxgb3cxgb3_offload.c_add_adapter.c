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
struct adapter {int /*<<< orphan*/  adapter_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  adapter_list ; 
 int /*<<< orphan*/  adapter_list_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void add_adapter(struct adapter *adap)
{
	write_lock_bh(&adapter_list_lock);
	list_add_tail(&adap->adapter_list, &adapter_list);
	write_unlock_bh(&adapter_list_lock);
}