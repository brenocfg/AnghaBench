#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvkm_secboot {int dummy; } ;
struct nvkm_msgqueue {int dummy; } ;
struct nvkm_falcon {int dummy; } ;
struct msgqueue_0148cdec {struct nvkm_msgqueue base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct msgqueue_0148cdec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgqueue_0148cdec_func ; 
 int /*<<< orphan*/  nvkm_msgqueue_ctor (int /*<<< orphan*/ *,struct nvkm_falcon*,struct nvkm_msgqueue*) ; 

int
msgqueue_0148cdec_new(struct nvkm_falcon *falcon, const struct nvkm_secboot *sb,
		      struct nvkm_msgqueue **queue)
{
	struct msgqueue_0148cdec *ret;

	ret = kzalloc(sizeof(*ret), GFP_KERNEL);
	if (!ret)
		return -ENOMEM;

	*queue = &ret->base;

	nvkm_msgqueue_ctor(&msgqueue_0148cdec_func, falcon, &ret->base);

	return 0;
}