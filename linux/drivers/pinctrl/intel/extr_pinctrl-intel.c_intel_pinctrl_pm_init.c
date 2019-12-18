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
typedef  int /*<<< orphan*/  u32 ;
struct intel_pinctrl_soc_data {int npins; } ;
struct TYPE_2__ {struct intel_community_context* communities; struct intel_pad_context* pads; } ;
struct intel_pinctrl {int ncommunities; TYPE_1__ context; int /*<<< orphan*/  dev; struct intel_community* communities; struct intel_pinctrl_soc_data* soc; } ;
struct intel_pad_context {int dummy; } ;
struct intel_community_context {int /*<<< orphan*/ * hostown; int /*<<< orphan*/ * intmask; } ;
struct intel_community {int ngpps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pinctrl_pm_init(struct intel_pinctrl *pctrl)
{
#ifdef CONFIG_PM_SLEEP
	const struct intel_pinctrl_soc_data *soc = pctrl->soc;
	struct intel_community_context *communities;
	struct intel_pad_context *pads;
	int i;

	pads = devm_kcalloc(pctrl->dev, soc->npins, sizeof(*pads), GFP_KERNEL);
	if (!pads)
		return -ENOMEM;

	communities = devm_kcalloc(pctrl->dev, pctrl->ncommunities,
				   sizeof(*communities), GFP_KERNEL);
	if (!communities)
		return -ENOMEM;


	for (i = 0; i < pctrl->ncommunities; i++) {
		struct intel_community *community = &pctrl->communities[i];
		u32 *intmask, *hostown;

		intmask = devm_kcalloc(pctrl->dev, community->ngpps,
				       sizeof(*intmask), GFP_KERNEL);
		if (!intmask)
			return -ENOMEM;

		communities[i].intmask = intmask;

		hostown = devm_kcalloc(pctrl->dev, community->ngpps,
				       sizeof(*hostown), GFP_KERNEL);
		if (!hostown)
			return -ENOMEM;

		communities[i].hostown = hostown;
	}

	pctrl->context.pads = pads;
	pctrl->context.communities = communities;
#endif

	return 0;
}