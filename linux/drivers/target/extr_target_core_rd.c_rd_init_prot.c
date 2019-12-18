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
struct TYPE_2__ {int /*<<< orphan*/  block_size; int /*<<< orphan*/  pi_prot_type; } ;
struct se_device {TYPE_1__ dev_attrib; int /*<<< orphan*/  prot_length; } ;
struct rd_dev {int dummy; } ;

/* Variables and functions */
 struct rd_dev* RD_DEV (struct se_device*) ; 
 int rd_build_prot_space (struct rd_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rd_init_prot(struct se_device *dev)
{
	struct rd_dev *rd_dev = RD_DEV(dev);

        if (!dev->dev_attrib.pi_prot_type)
		return 0;

	return rd_build_prot_space(rd_dev, dev->prot_length,
				   dev->dev_attrib.block_size);
}