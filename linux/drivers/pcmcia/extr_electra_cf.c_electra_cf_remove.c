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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct electra_cf_socket {int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_base; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem_phys; int /*<<< orphan*/  gpio_base; int /*<<< orphan*/  mem_base; int /*<<< orphan*/  io_virt; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; int /*<<< orphan*/  socket; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iounmap_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct electra_cf_socket* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct electra_cf_socket*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct electra_cf_socket*) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int electra_cf_remove(struct platform_device *ofdev)
{
	struct device *device = &ofdev->dev;
	struct electra_cf_socket *cf;

	cf = dev_get_drvdata(device);

	cf->active = 0;
	pcmcia_unregister_socket(&cf->socket);
	free_irq(cf->irq, cf);
	del_timer_sync(&cf->timer);

	__iounmap_at(cf->io_virt, cf->io_size);
	iounmap(cf->mem_base);
	iounmap(cf->gpio_base);
	release_mem_region(cf->mem_phys, cf->mem_size);
	release_region(cf->io_base, cf->io_size);

	kfree(cf);

	return 0;
}