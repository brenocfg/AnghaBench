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
struct nvkm_clk {int dummy; } ;
struct gf100_clk {int /*<<< orphan*/  eng; } ;

/* Variables and functions */
 struct gf100_clk* gf100_clk (struct nvkm_clk*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
gf100_clk_tidy(struct nvkm_clk *base)
{
	struct gf100_clk *clk = gf100_clk(base);
	memset(clk->eng, 0x00, sizeof(clk->eng));
}