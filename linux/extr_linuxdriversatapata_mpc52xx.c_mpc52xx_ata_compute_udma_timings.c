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
struct udmaspec {int tdh; int tli; int tsr; int tack; scalar_t__ tzah; scalar_t__ trp; scalar_t__ trfs; scalar_t__ tss; scalar_t__ tenv; scalar_t__ taz; scalar_t__ tmli; scalar_t__ tfs; scalar_t__ tdvh; scalar_t__ tdvs; scalar_t__ tds; scalar_t__ tcyc; scalar_t__ t2cyc; } ;
struct mpc52xx_ata_timings {int udma1; int udma2; int udma3; int udma4; int udma5; int using_udma; } ;
struct mpc52xx_ata_priv {struct udmaspec* udmaspec; struct mpc52xx_ata_timings* timings; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
mpc52xx_ata_compute_udma_timings(struct mpc52xx_ata_priv *priv, int dev,
				 int speed)
{
	struct mpc52xx_ata_timings *t = &priv->timings[dev];
	const struct udmaspec *s = &priv->udmaspec[speed];

	if (speed < 0 || speed > 2)
		return -EINVAL;

	t->udma1 = ((u32)s->t2cyc << 24) | ((u32)s->tcyc << 16) | ((u32)s->tds << 8) | s->tdh;
	t->udma2 = ((u32)s->tdvs << 24) | ((u32)s->tdvh << 16) | ((u32)s->tfs << 8) | s->tli;
	t->udma3 = ((u32)s->tmli << 24) | ((u32)s->taz << 16) | ((u32)s->tenv << 8) | s->tsr;
	t->udma4 = ((u32)s->tss << 24) | ((u32)s->trfs << 16) | ((u32)s->trp << 8) | s->tack;
	t->udma5 = (u32)s->tzah << 24;
	t->using_udma = 1;

	return 0;
}