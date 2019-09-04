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
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nv04_fifo_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ ,struct nvkm_fifo**) ; 
 int /*<<< orphan*/  nv10_fifo ; 
 int /*<<< orphan*/  nv10_fifo_ramfc ; 

int
nv10_fifo_new(struct nvkm_device *device, int index, struct nvkm_fifo **pfifo)
{
	return nv04_fifo_new_(&nv10_fifo, device, index, 32,
			      nv10_fifo_ramfc, pfifo);
}