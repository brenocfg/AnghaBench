#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtk_eth {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct TYPE_5__ {int cap_bit; int (* set_path ) (struct mtk_eth*,int) ;int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int) ; 
 int MTK_MUX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* mtk_eth_muxc ; 
 int /*<<< orphan*/  mtk_eth_path_name (int) ; 
 int stub1 (struct mtk_eth*,int) ; 

__attribute__((used)) static int mtk_eth_mux_setup(struct mtk_eth *eth, int path)
{
	int i, err = 0;

	if (!MTK_HAS_CAPS(eth->soc->caps, path)) {
		dev_err(eth->dev, "path %s isn't support on the SoC\n",
			mtk_eth_path_name(path));
		return -EINVAL;
	}

	if (!MTK_HAS_CAPS(eth->soc->caps, MTK_MUX))
		return 0;

	/* Setup MUX in path fabric */
	for (i = 0; i < ARRAY_SIZE(mtk_eth_muxc); i++) {
		if (MTK_HAS_CAPS(eth->soc->caps, mtk_eth_muxc[i].cap_bit)) {
			err = mtk_eth_muxc[i].set_path(eth, path);
			if (err)
				goto out;
		} else {
			dev_dbg(eth->dev, "mux %s isn't present on the SoC\n",
				mtk_eth_muxc[i].name);
		}
	}

out:
	return err;
}