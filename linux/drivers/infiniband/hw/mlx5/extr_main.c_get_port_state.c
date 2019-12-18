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
typedef  int /*<<< orphan*/  u8 ;
struct ib_port_attr {int state; } ;
struct TYPE_2__ {int (* query_port ) (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ;} ;
struct ib_device {TYPE_1__ ops; } ;
typedef  enum ib_port_state { ____Placeholder_ib_port_state } ib_port_state ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

__attribute__((used)) static int get_port_state(struct ib_device *ibdev,
			  u8 port_num,
			  enum ib_port_state *state)
{
	struct ib_port_attr attr;
	int ret;

	memset(&attr, 0, sizeof(attr));
	ret = ibdev->ops.query_port(ibdev, port_num, &attr);
	if (!ret)
		*state = attr.state;
	return ret;
}