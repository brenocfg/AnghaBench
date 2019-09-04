#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sh_dmae_device {int chcr_ie_bit; TYPE_1__* pdata; } ;
struct sh_dmae_chan {int dummy; } ;
struct TYPE_2__ {scalar_t__ needs_tend_set; } ;

/* Variables and functions */
 int CHCR_DE ; 
 int CHCR_TE ; 
 int /*<<< orphan*/  TEND ; 
 int chcr_read (struct sh_dmae_chan*) ; 
 int /*<<< orphan*/  chcr_write (struct sh_dmae_chan*,int) ; 
 int /*<<< orphan*/  sh_dmae_writel (struct sh_dmae_chan*,int,int /*<<< orphan*/ ) ; 
 struct sh_dmae_device* to_sh_dev (struct sh_dmae_chan*) ; 

__attribute__((used)) static void dmae_start(struct sh_dmae_chan *sh_chan)
{
	struct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	u32 chcr = chcr_read(sh_chan);

	if (shdev->pdata->needs_tend_set)
		sh_dmae_writel(sh_chan, 0xFFFFFFFF, TEND);

	chcr |= CHCR_DE | shdev->chcr_ie_bit;
	chcr_write(sh_chan, chcr & ~CHCR_TE);
}