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
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int MODE_MULT_CHAN_DOWN ; 
 int MODE_MULT_CHAN_UP ; 
 int MODE_SINGLE_CHAN ; 
 int MODE_SINGLE_CHAN_INTERVAL ; 

__attribute__((used)) static enum scan_mode labpc_ai_scan_mode(const struct comedi_cmd *cmd)
{
	unsigned int chan0;
	unsigned int chan1;

	if (cmd->chanlist_len == 1)
		return MODE_SINGLE_CHAN;

	/* chanlist may be NULL during cmdtest */
	if (!cmd->chanlist)
		return MODE_MULT_CHAN_UP;

	chan0 = CR_CHAN(cmd->chanlist[0]);
	chan1 = CR_CHAN(cmd->chanlist[1]);

	if (chan0 < chan1)
		return MODE_MULT_CHAN_UP;

	if (chan0 > chan1)
		return MODE_MULT_CHAN_DOWN;

	return MODE_SINGLE_CHAN_INTERVAL;
}