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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ mthd; int /*<<< orphan*/ * data; } ;
struct nvkm_memx {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memx_out (struct nvkm_memx*) ; 

__attribute__((used)) static void
memx_cmd(struct nvkm_memx *memx, u32 mthd, u32 size, u32 data[])
{
	if ((memx->c.size + size >= ARRAY_SIZE(memx->c.data)) ||
	    (memx->c.mthd && memx->c.mthd != mthd))
		memx_out(memx);
	memcpy(&memx->c.data[memx->c.size], data, size * sizeof(data[0]));
	memx->c.size += size;
	memx->c.mthd  = mthd;
}