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
struct ipr_resource_entry {scalar_t__ res_handle; } ;
struct TYPE_2__ {scalar_t__ res_handle; } ;
struct ipr_cmnd {TYPE_1__ ioarcb; } ;

/* Variables and functions */

__attribute__((used)) static int ipr_match_res(struct ipr_cmnd *ipr_cmd, void *resource)
{
	struct ipr_resource_entry *res = resource;

	if (res && ipr_cmd->ioarcb.res_handle == res->res_handle)
		return 1;
	return 0;
}