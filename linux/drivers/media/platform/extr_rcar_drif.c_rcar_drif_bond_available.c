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
struct rcar_drif_sdr {int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_ch_mask; struct rcar_drif** ch; } ;
struct rcar_drif {size_t num; struct rcar_drif_sdr* sdr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct rcar_drif* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcar_drif_bond_available(struct rcar_drif_sdr *sdr,
				    struct device_node *np)
{
	struct platform_device *pdev;
	struct rcar_drif *ch;
	int ret = 0;

	pdev = of_find_device_by_node(np);
	if (!pdev) {
		dev_err(sdr->dev, "failed to get bonded device from node\n");
		return -ENODEV;
	}

	device_lock(&pdev->dev);
	ch = platform_get_drvdata(pdev);
	if (ch) {
		/* Update sdr data in the bonded device */
		ch->sdr = sdr;

		/* Update sdr with bonded device data */
		sdr->ch[ch->num] = ch;
		sdr->hw_ch_mask |= BIT(ch->num);
	} else {
		/* Defer */
		dev_info(sdr->dev, "defer probe\n");
		ret = -EPROBE_DEFER;
	}
	device_unlock(&pdev->dev);

	put_device(&pdev->dev);

	return ret;
}