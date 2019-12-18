#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int created; } ;
struct TYPE_4__ {TYPE_1__ q; } ;
struct be_adapter {TYPE_2__ mcc_obj; } ;

/* Variables and functions */

__attribute__((used)) static bool use_mcc(struct be_adapter *adapter)
{
	return adapter->mcc_obj.q.created;
}