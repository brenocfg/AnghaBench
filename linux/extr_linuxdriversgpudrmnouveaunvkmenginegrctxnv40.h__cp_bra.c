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
typedef  int u32 ;
struct nvkm_grctx {int* ctxprog_label; } ;

/* Variables and functions */
 int CP_BRA ; 
 int CP_BRA_IF_CLEAR ; 
 int CP_BRA_IP_SHIFT ; 
 int /*<<< orphan*/  cp_out (struct nvkm_grctx*,int) ; 

__attribute__((used)) static inline void
_cp_bra(struct nvkm_grctx *ctx, u32 mod, int flag, int state, int name)
{
	int ip = 0;

	if (mod != 2) {
		ip = ctx->ctxprog_label[name] << CP_BRA_IP_SHIFT;
		if (ip == 0)
			ip = 0xff000000 | (name << CP_BRA_IP_SHIFT);
	}

	cp_out(ctx, CP_BRA | (mod << 18) | ip | flag |
		    (state ? 0 : CP_BRA_IF_CLEAR));
}