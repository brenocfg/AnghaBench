#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  fccp; } ;
struct TYPE_4__ {int /*<<< orphan*/  fecp; } ;
struct fs_enet_private {TYPE_3__ fcc; TYPE_1__ fec; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_pd_setup(struct fs_enet_private *fep)
{
	struct platform_device *ofdev = to_platform_device(fep->dev);

	fep->interrupt = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	if (!fep->interrupt)
		return -EINVAL;

	fep->fec.fecp = of_iomap(ofdev->dev.of_node, 0);
	if (!fep->fcc.fccp)
		return -EINVAL;

	return 0;
}