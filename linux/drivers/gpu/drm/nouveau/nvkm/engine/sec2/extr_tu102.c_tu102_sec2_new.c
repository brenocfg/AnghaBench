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
struct nvkm_sec2 {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_sec2_new_ (struct nvkm_device*,int,int,struct nvkm_sec2**) ; 

int
tu102_sec2_new(struct nvkm_device *device, int index,
	       struct nvkm_sec2 **psec2)
{
	/* TOP info wasn't updated on Turing to reflect the PRI
	 * address change for some reason.  We override it here.
	 */
	return nvkm_sec2_new_(device, index, 0x840000, psec2);
}