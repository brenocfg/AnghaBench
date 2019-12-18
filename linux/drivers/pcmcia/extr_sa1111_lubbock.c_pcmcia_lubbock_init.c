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
struct sa1111_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  lubbock_pcmcia_ops ; 
 int /*<<< orphan*/  pxa2xx_configure_sockets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa2xx_drv_pcmcia_add_one ; 
 int /*<<< orphan*/  pxa2xx_drv_pcmcia_ops (int /*<<< orphan*/ *) ; 
 int sa1111_pcmcia_add (struct sa1111_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pcmcia_lubbock_init(struct sa1111_dev *sadev)
{
	pxa2xx_drv_pcmcia_ops(&lubbock_pcmcia_ops);
	pxa2xx_configure_sockets(&sadev->dev, &lubbock_pcmcia_ops);
	return sa1111_pcmcia_add(sadev, &lubbock_pcmcia_ops,
				 pxa2xx_drv_pcmcia_add_one);
}