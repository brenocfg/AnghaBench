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
struct nvkm_instmem {TYPE_1__* func; } ;
struct TYPE_2__ {void (* wr32 ) (struct nvkm_instmem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void stub1 (struct nvkm_instmem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nvkm_instmem_wr32(struct nvkm_instmem *imem, u32 addr, u32 data)
{
	return imem->func->wr32(imem, addr, data);
}