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
struct nvkm_fuse {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct nvkm_fuse*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_fuse*,int /*<<< orphan*/ ) ; 

u32
nvkm_fuse_read(struct nvkm_fuse *fuse, u32 addr)
{
	return fuse->func->read(fuse, addr);
}