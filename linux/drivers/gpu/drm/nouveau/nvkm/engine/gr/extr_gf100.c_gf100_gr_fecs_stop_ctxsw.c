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
struct nvkm_gr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  disable; } ;
struct gf100_gr {TYPE_1__ fecs; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 
 int gf100_gr_fecs_ctrl_ctxsw (struct gf100_gr*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
gf100_gr_fecs_stop_ctxsw(struct nvkm_gr *base)
{
	struct gf100_gr *gr = gf100_gr(base);
	int ret = 0;

	mutex_lock(&gr->fecs.mutex);
	if (!gr->fecs.disable++) {
		if (WARN_ON(ret = gf100_gr_fecs_ctrl_ctxsw(gr, 0x38)))
			gr->fecs.disable--;
	}
	mutex_unlock(&gr->fecs.mutex);
	return ret;
}