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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int nvkm_object_ntfy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_event**) ; 
 TYPE_1__* nvkm_oproxy (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_oproxy_ntfy(struct nvkm_object *object, u32 mthd,
		 struct nvkm_event **pevent)
{
	return nvkm_object_ntfy(nvkm_oproxy(object)->object, mthd, pevent);
}