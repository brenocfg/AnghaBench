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
struct ipu_image_convert_chan {int out_eof_irq; int rot_out_eof_irq; int /*<<< orphan*/ * rotation_out_chan; int /*<<< orphan*/ * rotation_in_chan; int /*<<< orphan*/ * out_chan; int /*<<< orphan*/ * in_chan; int /*<<< orphan*/ * ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct ipu_image_convert_chan*) ; 
 int /*<<< orphan*/  ipu_ic_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_idmac_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_ipu_resources(struct ipu_image_convert_chan *chan)
{
	if (chan->out_eof_irq >= 0)
		free_irq(chan->out_eof_irq, chan);
	if (chan->rot_out_eof_irq >= 0)
		free_irq(chan->rot_out_eof_irq, chan);

	if (!IS_ERR_OR_NULL(chan->in_chan))
		ipu_idmac_put(chan->in_chan);
	if (!IS_ERR_OR_NULL(chan->out_chan))
		ipu_idmac_put(chan->out_chan);
	if (!IS_ERR_OR_NULL(chan->rotation_in_chan))
		ipu_idmac_put(chan->rotation_in_chan);
	if (!IS_ERR_OR_NULL(chan->rotation_out_chan))
		ipu_idmac_put(chan->rotation_out_chan);
	if (!IS_ERR_OR_NULL(chan->ic))
		ipu_ic_put(chan->ic);

	chan->in_chan = chan->out_chan = chan->rotation_in_chan =
		chan->rotation_out_chan = NULL;
	chan->out_eof_irq = chan->rot_out_eof_irq = -1;
}