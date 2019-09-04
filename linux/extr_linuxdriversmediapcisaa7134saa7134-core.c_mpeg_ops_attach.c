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
struct saa7134_mpeg_ops {scalar_t__ type; int (* init ) (struct saa7134_dev*) ;} ;
struct saa7134_dev {size_t board; struct saa7134_mpeg_ops* mops; } ;
struct TYPE_2__ {scalar_t__ mpeg; } ;

/* Variables and functions */
 TYPE_1__* saa7134_boards ; 
 int stub1 (struct saa7134_dev*) ; 

__attribute__((used)) static void mpeg_ops_attach(struct saa7134_mpeg_ops *ops,
			    struct saa7134_dev *dev)
{
	int err;

	if (NULL != dev->mops)
		return;
	if (saa7134_boards[dev->board].mpeg != ops->type)
		return;
	err = ops->init(dev);
	if (0 != err)
		return;
	dev->mops = ops;
}