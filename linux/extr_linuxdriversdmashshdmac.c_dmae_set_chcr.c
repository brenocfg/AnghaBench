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
typedef  int /*<<< orphan*/  u32 ;
struct sh_dmae_chan {int /*<<< orphan*/  xmit_shift; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  calc_xmit_shift (struct sh_dmae_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chcr_write (struct sh_dmae_chan*,int /*<<< orphan*/ ) ; 
 scalar_t__ dmae_is_busy (struct sh_dmae_chan*) ; 

__attribute__((used)) static int dmae_set_chcr(struct sh_dmae_chan *sh_chan, u32 val)
{
	/* If DMA is active, cannot set CHCR. TODO: remove this superfluous check */
	if (dmae_is_busy(sh_chan))
		return -EBUSY;

	sh_chan->xmit_shift = calc_xmit_shift(sh_chan, val);
	chcr_write(sh_chan, val);

	return 0;
}