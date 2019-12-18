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
typedef  int u64 ;
typedef  int u32 ;
struct msm_gpu {int dummy; } ;
struct a6xx_registers {int count; int* registers; int val0; int /*<<< orphan*/  val1; } ;
struct a6xx_gpu_state_obj {int /*<<< orphan*/  data; struct a6xx_registers const* handle; } ;
struct a6xx_gpu_state {int dummy; } ;
struct a6xx_crashdumper {int* ptr; int iova; } ;

/* Variables and functions */
 int A6XX_CD_DATA_OFFSET ; 
 int A6XX_CD_DATA_SIZE ; 
 int /*<<< orphan*/  CRASHDUMP_FINI (int*) ; 
 scalar_t__ CRASHDUMP_READ (int*,int,int,int) ; 
 scalar_t__ CRASHDUMP_WRITE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RANGE (int*,int) ; 
 int REG_A6XX_HLSQ_DBG_AHB_READ_APERTURE ; 
 int /*<<< orphan*/  REG_A6XX_HLSQ_DBG_READ_SEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ a6xx_crashdumper_run (struct msm_gpu*,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/  state_kmemdup (struct a6xx_gpu_state*,int*,int) ; 

__attribute__((used)) static void a6xx_get_crashdumper_hlsq_registers(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state,
		const struct a6xx_registers *regs,
		struct a6xx_gpu_state_obj *obj,
		struct a6xx_crashdumper *dumper)

{
	u64 *in = dumper->ptr;
	u64 out = dumper->iova + A6XX_CD_DATA_OFFSET;
	int i, regcount = 0;

	in += CRASHDUMP_WRITE(in, REG_A6XX_HLSQ_DBG_READ_SEL, regs->val1);

	for (i = 0; i < regs->count; i += 2) {
		u32 count = RANGE(regs->registers, i);
		u32 offset = REG_A6XX_HLSQ_DBG_AHB_READ_APERTURE +
			regs->registers[i] - (regs->val0 >> 2);

		in += CRASHDUMP_READ(in, offset, count, out);

		out += count * sizeof(u32);
		regcount += count;
	}

	CRASHDUMP_FINI(in);

	if (WARN_ON((regcount * sizeof(u32)) > A6XX_CD_DATA_SIZE))
		return;

	if (a6xx_crashdumper_run(gpu, dumper))
		return;

	obj->handle = regs;
	obj->data = state_kmemdup(a6xx_state, dumper->ptr + A6XX_CD_DATA_OFFSET,
		regcount * sizeof(u32));
}