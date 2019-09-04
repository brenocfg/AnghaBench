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
typedef  int /*<<< orphan*/  u8 ;
struct ib_port_modify {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int hns_roce_modify_port(struct ib_device *ib_dev, u8 port_num, int mask,
				struct ib_port_modify *props)
{
	return 0;
}