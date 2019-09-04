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
struct nvkm_fifo_chan {int dummy; } ;

/* Variables and functions */
 void* gf100_fifo_chan (struct nvkm_fifo_chan*) ; 

__attribute__((used)) static void *
gf100_fifo_gpfifo_dtor(struct nvkm_fifo_chan *base)
{
	return gf100_fifo_chan(base);
}