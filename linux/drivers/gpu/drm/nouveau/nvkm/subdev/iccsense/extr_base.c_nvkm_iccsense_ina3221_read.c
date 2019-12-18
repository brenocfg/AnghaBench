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
struct nvkm_iccsense_rail {int idx; int /*<<< orphan*/  mohm; TYPE_1__* sensor; } ;
struct nvkm_iccsense {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int nvkm_iccsense_poll_lane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvkm_iccsense_ina3221_read(struct nvkm_iccsense *iccsense,
			   struct nvkm_iccsense_rail *rail)
{
	return nvkm_iccsense_poll_lane(rail->sensor->i2c, rail->sensor->addr,
				       1 + (rail->idx * 2), 3,
				       2 + (rail->idx * 2), 3, rail->mohm,
				       40 * 8);
}