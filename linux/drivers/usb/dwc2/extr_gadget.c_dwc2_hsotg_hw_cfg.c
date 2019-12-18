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
typedef  int u32 ;
struct dwc2_hsotg_ep {int dummy; } ;
struct TYPE_2__ {int num_dev_ep; int dev_ep_dirs; scalar_t__ en_multiple_tx_fifo; int /*<<< orphan*/  total_fifo_size; } ;
struct dwc2_hsotg {int num_of_eps; int /*<<< orphan*/  fifo_mem; scalar_t__ dedicated_fifos; int /*<<< orphan*/  dev; TYPE_1__ hw_params; void** eps_out; void** eps_in; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_hsotg_hw_cfg(struct dwc2_hsotg *hsotg)
{
	u32 cfg;
	u32 ep_type;
	u32 i;

	/* check hardware configuration */

	hsotg->num_of_eps = hsotg->hw_params.num_dev_ep;

	/* Add ep0 */
	hsotg->num_of_eps++;

	hsotg->eps_in[0] = devm_kzalloc(hsotg->dev,
					sizeof(struct dwc2_hsotg_ep),
					GFP_KERNEL);
	if (!hsotg->eps_in[0])
		return -ENOMEM;
	/* Same dwc2_hsotg_ep is used in both directions for ep0 */
	hsotg->eps_out[0] = hsotg->eps_in[0];

	cfg = hsotg->hw_params.dev_ep_dirs;
	for (i = 1, cfg >>= 2; i < hsotg->num_of_eps; i++, cfg >>= 2) {
		ep_type = cfg & 3;
		/* Direction in or both */
		if (!(ep_type & 2)) {
			hsotg->eps_in[i] = devm_kzalloc(hsotg->dev,
				sizeof(struct dwc2_hsotg_ep), GFP_KERNEL);
			if (!hsotg->eps_in[i])
				return -ENOMEM;
		}
		/* Direction out or both */
		if (!(ep_type & 1)) {
			hsotg->eps_out[i] = devm_kzalloc(hsotg->dev,
				sizeof(struct dwc2_hsotg_ep), GFP_KERNEL);
			if (!hsotg->eps_out[i])
				return -ENOMEM;
		}
	}

	hsotg->fifo_mem = hsotg->hw_params.total_fifo_size;
	hsotg->dedicated_fifos = hsotg->hw_params.en_multiple_tx_fifo;

	dev_info(hsotg->dev, "EPs: %d, %s fifos, %d entries in SPRAM\n",
		 hsotg->num_of_eps,
		 hsotg->dedicated_fifos ? "dedicated" : "shared",
		 hsotg->fifo_mem);
	return 0;
}