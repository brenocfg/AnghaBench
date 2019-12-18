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
struct port_info {int dummy; } ;
struct c4iw_ep {int /*<<< orphan*/  rcv_win; int /*<<< orphan*/  snd_win; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_win ; 
 int /*<<< orphan*/  snd_win ; 

__attribute__((used)) static void set_tcp_window(struct c4iw_ep *ep, struct port_info *pi)
{
	ep->snd_win = snd_win;
	ep->rcv_win = rcv_win;
	pr_debug("snd_win %d rcv_win %d\n",
		 ep->snd_win, ep->rcv_win);
}