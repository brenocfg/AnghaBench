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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int ql_idc_wait (struct ql_adapter*) ; 
 int ql_mb_set_port_cfg (struct ql_adapter*) ; 

__attribute__((used)) static int ql_set_port_cfg(struct ql_adapter *qdev)
{
	int status;
	status = ql_mb_set_port_cfg(qdev);
	if (status)
		return status;
	status = ql_idc_wait(qdev);
	return status;
}