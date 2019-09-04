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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nvbios_init {int /*<<< orphan*/  head; TYPE_1__* subdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int nvkm_rdport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
init_rdport(struct nvbios_init *init, u16 port)
{
	if (init_exec(init))
		return nvkm_rdport(init->subdev->device, init->head, port);
	return 0x00;
}