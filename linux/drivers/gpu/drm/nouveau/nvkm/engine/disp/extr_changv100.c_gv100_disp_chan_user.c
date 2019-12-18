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
typedef  int u64 ;
struct TYPE_2__ {int user; } ;
struct nv50_disp_chan {TYPE_1__ chid; } ;

/* Variables and functions */

u64
gv100_disp_chan_user(struct nv50_disp_chan *chan, u64 *psize)
{
	*psize = 0x1000;
	return 0x690000 + ((chan->chid.user - 1) * 0x1000);
}