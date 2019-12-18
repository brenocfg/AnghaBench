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
struct pinctrl_dev {int dummy; } ;
struct npcm7xx_pinctrl {int /*<<< orphan*/  gcr_regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* npcm7xx_groups ; 
 int /*<<< orphan*/  npcm7xx_setfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct npcm7xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int npcm7xx_pinmux_set_mux(struct pinctrl_dev *pctldev,
				  unsigned int function,
				  unsigned int group)
{
	struct npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npcm->dev, "set_mux: %d, %d[%s]\n", function, group,
		npcm7xx_groups[group].name);

	npcm7xx_setfunc(npcm->gcr_regmap, npcm7xx_groups[group].pins,
			npcm7xx_groups[group].npins, group);

	return 0;
}