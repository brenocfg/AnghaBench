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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_port_pkey {int /*<<< orphan*/  port_num; int /*<<< orphan*/  pkey_index; TYPE_1__* sec; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct ib_device* dev; } ;

/* Variables and functions */
 int ib_get_cached_pkey (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ib_get_cached_subnet_prefix (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_pkey_and_subnet_prefix(struct ib_port_pkey *pp,
				      u16 *pkey,
				      u64 *subnet_prefix)
{
	struct ib_device *dev = pp->sec->dev;
	int ret;

	ret = ib_get_cached_pkey(dev, pp->port_num, pp->pkey_index, pkey);
	if (ret)
		return ret;

	ret = ib_get_cached_subnet_prefix(dev, pp->port_num, subnet_prefix);

	return ret;
}