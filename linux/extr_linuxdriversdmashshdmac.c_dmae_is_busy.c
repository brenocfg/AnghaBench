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
struct sh_dmae_chan {int dummy; } ;

/* Variables and functions */
 int CHCR_DE ; 
 int CHCR_TE ; 
 int chcr_read (struct sh_dmae_chan*) ; 

__attribute__((used)) static bool dmae_is_busy(struct sh_dmae_chan *sh_chan)
{
	u32 chcr = chcr_read(sh_chan);

	if ((chcr & (CHCR_DE | CHCR_TE)) == CHCR_DE)
		return true; /* working */

	return false; /* waiting */
}