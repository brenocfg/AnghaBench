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
struct gt215_ramfuc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ram_nsec (struct gt215_ramfuc*,int) ; 
 int ram_rd32 (struct gt215_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_wr32 (struct gt215_ramfuc*,int,int) ; 

__attribute__((used)) static void
nvkm_sddr3_dll_disable(struct gt215_ramfuc *fuc, u32 *mr)
{
	u32 mr1_old = ram_rd32(fuc, mr[1]);

	if (!(mr1_old & 0x1)) {
		ram_wr32(fuc, 0x1002d4, 0x00000001);
		ram_wr32(fuc, mr[1], mr[1]);
		ram_nsec(fuc, 1000);
	}
}