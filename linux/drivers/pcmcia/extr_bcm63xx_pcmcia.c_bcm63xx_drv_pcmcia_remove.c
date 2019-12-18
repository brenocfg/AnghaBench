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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct bcm63xx_pcmcia_socket {struct resource* reg_res; int /*<<< orphan*/  io_base; int /*<<< orphan*/  base; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bcm63xx_pcmcia_socket*) ; 
 struct bcm63xx_pcmcia_socket* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int bcm63xx_drv_pcmcia_remove(struct platform_device *pdev)
{
	struct bcm63xx_pcmcia_socket *skt;
	struct resource *res;

	skt = platform_get_drvdata(pdev);
	del_timer_sync(&skt->timer);
	iounmap(skt->base);
	iounmap(skt->io_base);
	res = skt->reg_res;
	release_mem_region(res->start, resource_size(res));
	kfree(skt);
	return 0;
}