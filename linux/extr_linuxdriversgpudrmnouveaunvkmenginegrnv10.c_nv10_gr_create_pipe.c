#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pipe_state {int /*<<< orphan*/ * pipe_0x0040; int /*<<< orphan*/ * pipe_0x0000; int /*<<< orphan*/ * pipe_0x4400; int /*<<< orphan*/ * pipe_0x7800; int /*<<< orphan*/ * pipe_0x7400; int /*<<< orphan*/ * pipe_0x7000; int /*<<< orphan*/ * pipe_0x6c00; int /*<<< orphan*/ * pipe_0x6800; int /*<<< orphan*/ * pipe_0x6400; int /*<<< orphan*/ * pipe_0x0200; } ;
struct nvkm_subdev {int dummy; } ;
struct nv10_gr_chan {struct pipe_state pipe_state; struct nv10_gr* gr; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct nv10_gr {TYPE_2__ base; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv10_gr_create_pipe(struct nv10_gr_chan *chan)
{
	struct nv10_gr *gr = chan->gr;
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct pipe_state *pipe_state = &chan->pipe_state;
	u32 *pipe_state_addr;
	int i;
#define PIPE_INIT(addr) \
	do { \
		pipe_state_addr = pipe_state->pipe_##addr; \
	} while (0)
#define PIPE_INIT_END(addr) \
	do { \
		u32 *__end_addr = pipe_state->pipe_##addr + \
				ARRAY_SIZE(pipe_state->pipe_##addr); \
		if (pipe_state_addr != __end_addr) \
			nvkm_error(subdev, "incomplete pipe init for 0x%x :  %p/%p\n", \
				addr, pipe_state_addr, __end_addr); \
	} while (0)
#define NV_WRITE_PIPE_INIT(value) *(pipe_state_addr++) = value

	PIPE_INIT(0x0200);
	for (i = 0; i < 48; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0200);

	PIPE_INIT(0x6400);
	for (i = 0; i < 211; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f000000);
	NV_WRITE_PIPE_INIT(0x3f000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	PIPE_INIT_END(0x6400);

	PIPE_INIT(0x6800);
	for (i = 0; i < 162; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	for (i = 0; i < 25; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x6800);

	PIPE_INIT(0x6c00);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0xbf800000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x6c00);

	PIPE_INIT(0x7000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	for (i = 0; i < 35; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7000);

	PIPE_INIT(0x7400);
	for (i = 0; i < 48; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7400);

	PIPE_INIT(0x7800);
	for (i = 0; i < 48; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7800);

	PIPE_INIT(0x4400);
	for (i = 0; i < 32; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x4400);

	PIPE_INIT(0x0000);
	for (i = 0; i < 16; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0000);

	PIPE_INIT(0x0040);
	for (i = 0; i < 4; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0040);

#undef PIPE_INIT
#undef PIPE_INIT_END
#undef NV_WRITE_PIPE_INIT
}