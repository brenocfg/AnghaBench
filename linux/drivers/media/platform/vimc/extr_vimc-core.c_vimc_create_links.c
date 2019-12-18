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
struct vimc_ent_link {size_t src_ent; size_t sink_ent; int /*<<< orphan*/  flags; int /*<<< orphan*/  sink_pad; int /*<<< orphan*/  src_pad; } ;
struct vimc_ent_device {int /*<<< orphan*/  ent; } ;
struct vimc_device {int /*<<< orphan*/ * subdevs; TYPE_1__* pipe_cfg; } ;
struct TYPE_2__ {unsigned int num_links; struct vimc_ent_link* links; } ;

/* Variables and functions */
 int media_create_pad_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vimc_ent_device* platform_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vimc_create_links(struct vimc_device *vimc)
{
	unsigned int i;
	int ret;

	/* Initialize the links between entities */
	for (i = 0; i < vimc->pipe_cfg->num_links; i++) {
		const struct vimc_ent_link *link = &vimc->pipe_cfg->links[i];
		/*
		 * TODO: Check another way of retrieving ved struct without
		 * relying on platform_get_drvdata
		 */
		struct vimc_ent_device *ved_src =
			platform_get_drvdata(vimc->subdevs[link->src_ent]);
		struct vimc_ent_device *ved_sink =
			platform_get_drvdata(vimc->subdevs[link->sink_ent]);

		ret = media_create_pad_link(ved_src->ent, link->src_pad,
					    ved_sink->ent, link->sink_pad,
					    link->flags);
		if (ret)
			return ret;
	}

	return 0;
}