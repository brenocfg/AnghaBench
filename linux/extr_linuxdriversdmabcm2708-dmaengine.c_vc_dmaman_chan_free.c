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
struct vc_dmaman {int chan_available; } ;

/* Variables and functions */
 int EIDRM ; 
 int EINVAL ; 

__attribute__((used)) static int vc_dmaman_chan_free(struct vc_dmaman *dmaman, int chan)
{
	if (chan < 0)
		return -EINVAL;

	if ((1 << chan) & dmaman->chan_available)
		return -EIDRM;

	dmaman->chan_available |= (1 << chan);

	return 0;
}