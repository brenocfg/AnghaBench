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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int nvkm_object_wr08 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* nvkm_oproxy (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_oproxy_wr08(struct nvkm_object *object, u64 addr, u8 data)
{
	return nvkm_object_wr08(nvkm_oproxy(object)->object, addr, data);
}