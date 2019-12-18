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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvkm_ltc {int /*<<< orphan*/  tag_base; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gm200_ltc_init(struct nvkm_ltc *ltc)
{
	nvkm_wr32(ltc->subdev.device, 0x17e278, ltc->tag_base);
}