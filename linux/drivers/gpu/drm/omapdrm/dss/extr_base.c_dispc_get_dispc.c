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
struct dss_device {struct dispc_device* dispc; } ;
struct dispc_device {int dummy; } ;

/* Variables and functions */

struct dispc_device *dispc_get_dispc(struct dss_device *dss)
{
	return dss->dispc;
}