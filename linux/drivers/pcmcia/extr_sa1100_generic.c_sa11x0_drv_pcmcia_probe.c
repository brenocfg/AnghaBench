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
struct soc_pcmcia_socket {int nr; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;
struct platform_device {int id; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct soc_pcmcia_socket* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  sa11x0_cf_ops ; 
 int sa11x0_drv_pcmcia_legacy_probe (struct platform_device*) ; 
 int sa11xx_drv_pcmcia_add_one (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  sa11xx_drv_pcmcia_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_pcmcia_init_one (struct soc_pcmcia_socket*,int /*<<< orphan*/ *,struct device*) ; 

__attribute__((used)) static int sa11x0_drv_pcmcia_probe(struct platform_device *pdev)
{
	struct soc_pcmcia_socket *skt;
	struct device *dev = &pdev->dev;

	if (pdev->id == -1)
		return sa11x0_drv_pcmcia_legacy_probe(pdev);

	skt = devm_kzalloc(dev, sizeof(*skt), GFP_KERNEL);
	if (!skt)
		return -ENOMEM;

	platform_set_drvdata(pdev, skt);

	skt->nr = pdev->id;
	skt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(skt->clk))
		return PTR_ERR(skt->clk);

	sa11xx_drv_pcmcia_ops(&sa11x0_cf_ops);
	soc_pcmcia_init_one(skt, &sa11x0_cf_ops, dev);

	return sa11xx_drv_pcmcia_add_one(skt);
}