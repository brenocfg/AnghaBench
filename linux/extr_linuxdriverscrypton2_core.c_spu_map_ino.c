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
struct spu_queue {int /*<<< orphan*/  irq_name; int /*<<< orphan*/  irq; int /*<<< orphan*/  devino; int /*<<< orphan*/  qhandle; } ;
struct spu_mdesc_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * irqs; } ;
struct platform_device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int EINVAL ; 
 int find_devino_index (struct platform_device*,struct spu_mdesc_info*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spu_queue*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 unsigned long sun4v_ncs_qhandle_to_devino (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spu_map_ino(struct platform_device *dev, struct spu_mdesc_info *ip,
		       const char *irq_name, struct spu_queue *p,
		       irq_handler_t handler)
{
	unsigned long herr;
	int index;

	herr = sun4v_ncs_qhandle_to_devino(p->qhandle, &p->devino);
	if (herr)
		return -EINVAL;

	index = find_devino_index(dev, ip, p->devino);
	if (index < 0)
		return index;

	p->irq = dev->archdata.irqs[index];

	sprintf(p->irq_name, "%s-%d", irq_name, index);

	return request_irq(p->irq, handler, 0, p->irq_name, p);
}