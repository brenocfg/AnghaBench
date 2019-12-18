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
struct nvkm_secboot {int dummy; } ;
struct nvkm_msgqueue {int dummy; } ;
struct nvkm_falcon {int dummy; } ;
struct TYPE_2__ {struct nvkm_msgqueue base; } ;
struct msgqueue_0137bca5 {TYPE_1__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct msgqueue_0137bca5* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgqueue_0137bca5_func ; 
 int /*<<< orphan*/  nvkm_msgqueue_ctor (int /*<<< orphan*/ *,struct nvkm_falcon*,struct nvkm_msgqueue*) ; 

int
msgqueue_0137bca5_new(struct nvkm_falcon *falcon, const struct nvkm_secboot *sb,
		      struct nvkm_msgqueue **queue)
{
	struct msgqueue_0137bca5 *ret;

	ret = kzalloc(sizeof(*ret), GFP_KERNEL);
	if (!ret)
		return -ENOMEM;

	*queue = &ret->base.base;

	/*
	 * FIXME this must be set to the address of a *GPU* mapping within the
	 * ACR address space!
	 */
	/* ret->wpr_addr = sb->wpr_addr; */

	nvkm_msgqueue_ctor(&msgqueue_0137bca5_func, falcon, &ret->base.base);

	return 0;
}