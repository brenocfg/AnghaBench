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
struct ql3_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ ql_is_fiber (struct ql3_adapter*) ; 
 int ql_is_full_dup (struct ql3_adapter*) ; 

__attribute__((used)) static int ql_is_link_full_dup(struct ql3_adapter *qdev)
{
	if (ql_is_fiber(qdev))
		return 1;
	else
		return ql_is_full_dup(qdev);
}