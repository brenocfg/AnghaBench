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
typedef  scalar_t__ u32 ;
struct cppi41_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cppi41_dd {scalar_t__ descs_phys; TYPE_1__ ddev; struct cppi41_channel** chan_busy; } ;
struct cppi41_channel {int dummy; } ;

/* Variables and functions */
 int ALLOC_DECS_NUM ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cppi41_channel *desc_to_chan(struct cppi41_dd *cdd, u32 desc)
{
	struct cppi41_channel *c;
	u32 descs_size;
	u32 desc_num;

	descs_size = sizeof(struct cppi41_desc) * ALLOC_DECS_NUM;

	if (!((desc >= cdd->descs_phys) &&
			(desc < (cdd->descs_phys + descs_size)))) {
		return NULL;
	}

	desc_num = (desc - cdd->descs_phys) / sizeof(struct cppi41_desc);
	BUG_ON(desc_num >= ALLOC_DECS_NUM);
	c = cdd->chan_busy[desc_num];
	cdd->chan_busy[desc_num] = NULL;

	/* Usecount for chan_busy[], paired with push_desc_queue() */
	pm_runtime_put(cdd->ddev.dev);

	return c;
}