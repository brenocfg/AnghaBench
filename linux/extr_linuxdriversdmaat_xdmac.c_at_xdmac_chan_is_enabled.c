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
struct at_xdmac_chan {int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_XDMAC_GS ; 
 int at_xdmac_chan_read (struct at_xdmac_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool at_xdmac_chan_is_enabled(struct at_xdmac_chan *atchan)
{
	return at_xdmac_chan_read(atchan, AT_XDMAC_GS) & atchan->mask;
}