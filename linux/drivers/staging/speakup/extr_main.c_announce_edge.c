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
struct vc_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSG_EDGE_MSGS_START ; 
 int /*<<< orphan*/  bleep (int /*<<< orphan*/ ) ; 
 int edge_quiet ; 
 int spk_bleeps ; 
 int /*<<< orphan*/  spk_msg_get (scalar_t__) ; 
 int /*<<< orphan*/  spk_y ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void announce_edge(struct vc_data *vc, int msg_id)
{
	if (spk_bleeps & 1)
		bleep(spk_y);
	if ((spk_bleeps & 2) && (msg_id < edge_quiet))
		synth_printf("%s\n",
			     spk_msg_get(MSG_EDGE_MSGS_START + msg_id - 1));
}