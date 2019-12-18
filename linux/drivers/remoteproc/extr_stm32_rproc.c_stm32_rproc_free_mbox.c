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
struct stm32_rproc {TYPE_1__* mb; } ;
struct rproc {struct stm32_rproc* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * chan; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_rproc_free_mbox(struct rproc *rproc)
{
	struct stm32_rproc *ddata = rproc->priv;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(ddata->mb); i++) {
		if (ddata->mb[i].chan)
			mbox_free_channel(ddata->mb[i].chan);
		ddata->mb[i].chan = NULL;
	}
}