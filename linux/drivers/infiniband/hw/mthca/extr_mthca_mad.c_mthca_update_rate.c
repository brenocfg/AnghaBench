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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mthca_dev {int* rate; TYPE_1__ ib_dev; } ;
struct ib_port_attr {int active_speed; int /*<<< orphan*/  active_width; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int ib_query_port (TYPE_1__*,int,struct ib_port_attr*) ; 
 int ib_width_enum_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_port_attr*) ; 
 struct ib_port_attr* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_update_rate(struct mthca_dev *dev, u8 port_num)
{
	struct ib_port_attr *tprops = NULL;
	int                  ret;

	tprops = kmalloc(sizeof *tprops, GFP_KERNEL);
	if (!tprops)
		return -ENOMEM;

	ret = ib_query_port(&dev->ib_dev, port_num, tprops);
	if (ret) {
		dev_warn(&dev->ib_dev.dev,
			 "ib_query_port failed (%d) forport %d\n", ret,
			 port_num);
		goto out;
	}

	dev->rate[port_num - 1] = tprops->active_speed *
				  ib_width_enum_to_int(tprops->active_width);

out:
	kfree(tprops);
	return ret;
}