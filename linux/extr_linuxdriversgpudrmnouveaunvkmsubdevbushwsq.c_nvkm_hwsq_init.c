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
struct nvkm_subdev {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct nvkm_hwsq {TYPE_1__ c; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; struct nvkm_subdev* subdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_hwsq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

int
nvkm_hwsq_init(struct nvkm_subdev *subdev, struct nvkm_hwsq **phwsq)
{
	struct nvkm_hwsq *hwsq;

	hwsq = *phwsq = kmalloc(sizeof(*hwsq), GFP_KERNEL);
	if (hwsq) {
		hwsq->subdev = subdev;
		hwsq->addr = ~0;
		hwsq->data = ~0;
		memset(hwsq->c.data, 0x7f, sizeof(hwsq->c.data));
		hwsq->c.size = 0;
	}

	return hwsq ? 0 : -ENOMEM;
}