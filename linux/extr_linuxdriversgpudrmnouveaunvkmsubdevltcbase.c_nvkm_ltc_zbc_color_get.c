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
struct nvkm_ltc {TYPE_1__* func; int /*<<< orphan*/ * zbc_color; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* zbc_clear_color ) (struct nvkm_ltc*,int,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_ltc*,int,int /*<<< orphan*/  const*) ; 

int
nvkm_ltc_zbc_color_get(struct nvkm_ltc *ltc, int index, const u32 color[4])
{
	memcpy(ltc->zbc_color[index], color, sizeof(ltc->zbc_color[index]));
	ltc->func->zbc_clear_color(ltc, index, color);
	return index;
}