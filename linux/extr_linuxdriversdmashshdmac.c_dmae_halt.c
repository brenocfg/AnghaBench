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
struct sh_dmae_device {int chcr_ie_bit; } ;
struct sh_dmae_chan {int dummy; } ;

/* Variables and functions */
 int CHCR_DE ; 
 int CHCR_TE ; 
 int chcr_read (struct sh_dmae_chan*) ; 
 int /*<<< orphan*/  chcr_write (struct sh_dmae_chan*,int) ; 
 struct sh_dmae_device* to_sh_dev (struct sh_dmae_chan*) ; 

__attribute__((used)) static void dmae_halt(struct sh_dmae_chan *sh_chan)
{
	struct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	u32 chcr = chcr_read(sh_chan);

	chcr &= ~(CHCR_DE | CHCR_TE | shdev->chcr_ie_bit);
	chcr_write(sh_chan, chcr);
}