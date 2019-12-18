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
struct nvkm_iccsense_rail {int dummy; } ;
struct nvkm_iccsense {int dummy; } ;

/* Variables and functions */
 int nvkm_iccsense_ina2x9_read (struct nvkm_iccsense*,struct nvkm_iccsense_rail*,int,int) ; 

__attribute__((used)) static int
nvkm_iccsense_ina209_read(struct nvkm_iccsense *iccsense,
			  struct nvkm_iccsense_rail *rail)
{
	return nvkm_iccsense_ina2x9_read(iccsense, rail, 3, 4);
}