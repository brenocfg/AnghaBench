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
struct saa7134_mpeg_ops {int /*<<< orphan*/  (* fini ) (struct saa7134_dev*) ;} ;
struct saa7134_dev {struct saa7134_mpeg_ops* mops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct saa7134_dev*) ; 

__attribute__((used)) static void mpeg_ops_detach(struct saa7134_mpeg_ops *ops,
			    struct saa7134_dev *dev)
{
	if (NULL == dev->mops)
		return;
	if (dev->mops != ops)
		return;
	dev->mops->fini(dev);
	dev->mops = NULL;
}