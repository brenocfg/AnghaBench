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
typedef  int u64 ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int ql_run_loopback_test (struct ql_adapter*) ; 
 int ql_start_loopback (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_stop_loopback (struct ql_adapter*) ; 

__attribute__((used)) static int ql_loopback_test(struct ql_adapter *qdev, u64 *data)
{
	*data = ql_start_loopback(qdev);
	if (*data)
		goto out;
	*data = ql_run_loopback_test(qdev);
out:
	ql_stop_loopback(qdev);
	return *data;
}