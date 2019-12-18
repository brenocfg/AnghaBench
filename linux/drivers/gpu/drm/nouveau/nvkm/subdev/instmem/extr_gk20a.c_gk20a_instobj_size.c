#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct nvkm_memory {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mn; } ;
struct TYPE_3__ {scalar_t__ length; } ;

/* Variables and functions */
 TYPE_2__* gk20a_instobj (struct nvkm_memory*) ; 

__attribute__((used)) static u64
gk20a_instobj_size(struct nvkm_memory *memory)
{
	return (u64)gk20a_instobj(memory)->mn->length << 12;
}