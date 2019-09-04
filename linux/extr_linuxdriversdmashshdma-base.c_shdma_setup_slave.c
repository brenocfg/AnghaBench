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
struct shdma_ops {int (* set_slave ) (struct shdma_chan*,int,int /*<<< orphan*/ ,int) ;} ;
struct shdma_dev {struct shdma_ops* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct shdma_chan {int hw_req; int real_slave_id; int slave_id; TYPE_2__* dev; TYPE_1__ dma_chan; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shdma_slave_used ; 
 int slave_num ; 
 int stub1 (struct shdma_chan*,int,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct shdma_chan*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 struct shdma_dev* to_shdma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shdma_setup_slave(struct shdma_chan *schan, dma_addr_t slave_addr)
{
	struct shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	const struct shdma_ops *ops = sdev->ops;
	int ret, match;

	if (schan->dev->of_node) {
		match = schan->hw_req;
		ret = ops->set_slave(schan, match, slave_addr, true);
		if (ret < 0)
			return ret;
	} else {
		match = schan->real_slave_id;
	}

	if (schan->real_slave_id < 0 || schan->real_slave_id >= slave_num)
		return -EINVAL;

	if (test_and_set_bit(schan->real_slave_id, shdma_slave_used))
		return -EBUSY;

	ret = ops->set_slave(schan, match, slave_addr, false);
	if (ret < 0) {
		clear_bit(schan->real_slave_id, shdma_slave_used);
		return ret;
	}

	schan->slave_id = schan->real_slave_id;

	return 0;
}