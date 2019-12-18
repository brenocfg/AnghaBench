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
struct ipu_prg_channel {size_t used_pre; } ;
struct ipu_prg {int /*<<< orphan*/ * pres; struct ipu_prg_channel* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_pre_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_prg_put_pre(struct ipu_prg *prg, int prg_chan)
{
	struct ipu_prg_channel *chan = &prg->chan[prg_chan];

	ipu_pre_put(prg->pres[chan->used_pre]);
	chan->used_pre = -1;
}