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
struct soc_pcmcia_socket {int nr; struct clk* clk; } ;
struct skt_dev_info {int nskt; struct soc_pcmcia_socket* skt; } ;
struct pcmcia_low_level {int dummy; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SKT_DEV_INFO_SIZE (int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct skt_dev_info*) ; 
 struct clk* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct skt_dev_info* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sa11xx_drv_pcmcia_add_one (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  sa11xx_drv_pcmcia_ops (struct pcmcia_low_level*) ; 
 int /*<<< orphan*/  soc_pcmcia_init_one (struct soc_pcmcia_socket*,struct pcmcia_low_level*,struct device*) ; 
 int /*<<< orphan*/  soc_pcmcia_remove_one (struct soc_pcmcia_socket*) ; 

int sa11xx_drv_pcmcia_probe(struct device *dev, struct pcmcia_low_level *ops,
			    int first, int nr)
{
	struct skt_dev_info *sinfo;
	struct soc_pcmcia_socket *skt;
	int i, ret = 0;
	struct clk *clk;

	clk = devm_clk_get(dev, NULL);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	sa11xx_drv_pcmcia_ops(ops);

	sinfo = devm_kzalloc(dev, SKT_DEV_INFO_SIZE(nr), GFP_KERNEL);
	if (!sinfo)
		return -ENOMEM;

	sinfo->nskt = nr;

	/* Initialize processor specific parameters */
	for (i = 0; i < nr; i++) {
		skt = &sinfo->skt[i];

		skt->nr = first + i;
		skt->clk = clk;
		soc_pcmcia_init_one(skt, ops, dev);

		ret = sa11xx_drv_pcmcia_add_one(skt);
		if (ret)
			break;
	}

	if (ret) {
		while (--i >= 0)
			soc_pcmcia_remove_one(&sinfo->skt[i]);
	} else {
		dev_set_drvdata(dev, sinfo);
	}

	return ret;
}