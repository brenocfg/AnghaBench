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
struct mthca_init_ib_param {int /*<<< orphan*/  pkey_cap; int /*<<< orphan*/  gid_cap; int /*<<< orphan*/  mtu_cap; int /*<<< orphan*/  vl_cap; int /*<<< orphan*/  port_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkey_table_len; int /*<<< orphan*/  gid_table_len; int /*<<< orphan*/  mtu_cap; int /*<<< orphan*/  vl_cap; int /*<<< orphan*/  port_width_cap; } ;
struct mthca_dev {TYPE_1__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mthca_init_ib_param*,int /*<<< orphan*/ ,int) ; 
 int mthca_INIT_IB (struct mthca_dev*,struct mthca_init_ib_param*,int) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,int) ; 

__attribute__((used)) static void init_port(struct mthca_dev *dev, int port)
{
	int err;
	struct mthca_init_ib_param param;

	memset(&param, 0, sizeof param);

	param.port_width = dev->limits.port_width_cap;
	param.vl_cap     = dev->limits.vl_cap;
	param.mtu_cap    = dev->limits.mtu_cap;
	param.gid_cap    = dev->limits.gid_table_len;
	param.pkey_cap   = dev->limits.pkey_table_len;

	err = mthca_INIT_IB(dev, &param, port);
	if (err)
		mthca_warn(dev, "INIT_IB failed, return code %d.\n", err);
}