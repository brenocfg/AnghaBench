#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmw_resource {TYPE_1__* func; } ;
struct TYPE_2__ {int needs_backup; } ;

/* Variables and functions */

bool vmw_resource_needs_backup(const struct vmw_resource *res)
{
	return res->func->needs_backup;
}