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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_msgqueue {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
init_gen_cmdline(struct nvkm_msgqueue *queue, void *buf)
{
	struct {
		u32 freq_hz;
		u32 falc_trace_size;
		u32 falc_trace_dma_base;
		u32 falc_trace_dma_idx;
		bool secure_mode;
	} *args = buf;

	args->secure_mode = false;
}