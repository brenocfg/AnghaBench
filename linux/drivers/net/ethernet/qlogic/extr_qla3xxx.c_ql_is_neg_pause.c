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
 int ql_is_petbi_neg_pause (struct ql3_adapter*) ; 
 int ql_is_phy_neg_pause (struct ql3_adapter*) ; 

__attribute__((used)) static int ql_is_neg_pause(struct ql3_adapter *qdev)
{
	if (ql_is_fiber(qdev))
		return ql_is_petbi_neg_pause(qdev);
	else
		return ql_is_phy_neg_pause(qdev);
}