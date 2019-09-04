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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nvkm_msgqueue {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
init_gen_cmdline(struct nvkm_msgqueue *queue, void *buf)
{
	struct {
		u32 reserved;
		u32 freq_hz;
		u32 trace_size;
		u32 trace_dma_base;
		u16 trace_dma_base1;
		u8 trace_dma_offset;
		u32 trace_dma_idx;
		bool secure_mode;
		bool raise_priv_sec;
		struct {
			u32 dma_base;
			u16 dma_base1;
			u8 dma_offset;
			u16 fb_size;
			u8 dma_idx;
		} gc6_ctx;
		u8 pad;
	} *args = buf;

	args->secure_mode = 1;
}