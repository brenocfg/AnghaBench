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
struct nvkm_grctx {int dummy; } ;

/* Variables and functions */
 int CP_SET ; 
 int CP_SET_1 ; 
 int /*<<< orphan*/  cp_out (struct nvkm_grctx*,int) ; 

__attribute__((used)) static inline void
_cp_set(struct nvkm_grctx *ctx, int flag, int state)
{
	cp_out(ctx, CP_SET | flag | (state ? CP_SET_1 : 0));
}