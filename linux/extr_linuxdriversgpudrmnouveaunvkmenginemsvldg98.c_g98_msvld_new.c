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
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g98_msvld ; 
 int nvkm_msvld_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_engine**) ; 

int
g98_msvld_new(struct nvkm_device *device, int index,
	      struct nvkm_engine **pengine)
{
	return nvkm_msvld_new_(&g98_msvld, device, index, pengine);
}