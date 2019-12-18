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
struct nvkm_grctx {int* ucode; scalar_t__ mode; int* ctxprog_label; int ctxprog_len; } ;

/* Variables and functions */
 int CP_BRA_IP ; 
 int CP_BRA_IP_SHIFT ; 
 scalar_t__ NVKM_GRCTX_PROG ; 

__attribute__((used)) static inline void
cp_name(struct nvkm_grctx *ctx, int name)
{
	u32 *ctxprog = ctx->ucode;
	int i;

	if (ctx->mode != NVKM_GRCTX_PROG)
		return;

	ctx->ctxprog_label[name] = ctx->ctxprog_len;
	for (i = 0; i < ctx->ctxprog_len; i++) {
		if ((ctxprog[i] & 0xfff00000) != 0xff400000)
			continue;
		if ((ctxprog[i] & CP_BRA_IP) != ((name) << CP_BRA_IP_SHIFT))
			continue;
		ctxprog[i] = (ctxprog[i] & 0x00ff00ff) |
			     (ctx->ctxprog_len << CP_BRA_IP_SHIFT);
	}
}