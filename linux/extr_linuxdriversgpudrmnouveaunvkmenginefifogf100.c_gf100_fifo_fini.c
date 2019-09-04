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
struct nvkm_fifo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct gf100_fifo {TYPE_1__ recover; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct gf100_fifo* gf100_fifo (struct nvkm_fifo*) ; 

__attribute__((used)) static void
gf100_fifo_fini(struct nvkm_fifo *base)
{
	struct gf100_fifo *fifo = gf100_fifo(base);
	flush_work(&fifo->recover.work);
}