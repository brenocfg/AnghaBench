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
typedef  size_t u8 ;
struct ib_gid_table {int dummy; } ;
struct ib_device {TYPE_2__* port_data; } ;
struct TYPE_3__ {struct ib_gid_table* gid; } ;
struct TYPE_4__ {TYPE_1__ cache; } ;

/* Variables and functions */

__attribute__((used)) static struct ib_gid_table *rdma_gid_table(struct ib_device *device, u8 port)
{
	return device->port_data[port].cache.gid;
}