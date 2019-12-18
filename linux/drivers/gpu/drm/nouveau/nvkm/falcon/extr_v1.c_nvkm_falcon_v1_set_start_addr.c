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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvkm_falcon_v1_set_start_addr(struct nvkm_falcon *falcon, u32 start_addr)
{
	nvkm_falcon_wr32(falcon, 0x104, start_addr);
}