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
typedef  int u32 ;
struct nvkm_ior {int id; } ;

/* Variables and functions */

__attribute__((used)) static inline u32
nv50_ior_base(struct nvkm_ior *ior)
{
	return ior->id * 0x800;
}