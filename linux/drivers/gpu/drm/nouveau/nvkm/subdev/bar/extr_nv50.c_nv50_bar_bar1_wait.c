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
struct nvkm_bar {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_bar_flush (struct nvkm_bar*) ; 

void
nv50_bar_bar1_wait(struct nvkm_bar *base)
{
	nvkm_bar_flush(base);
}