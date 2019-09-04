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
struct dpu_lm_cfg {int id; TYPE_1__* sblk; } ;
typedef  enum dpu_lm { ____Placeholder_dpu_lm } dpu_lm ;
struct TYPE_2__ {int maxblendstages; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int _mixer_stages(const struct dpu_lm_cfg *mixer, int count,
		enum dpu_lm lm)
{
	int i;
	int stages = -EINVAL;

	for (i = 0; i < count; i++) {
		if (lm == mixer[i].id) {
			stages = mixer[i].sblk->maxblendstages;
			break;
		}
	}

	return stages;
}