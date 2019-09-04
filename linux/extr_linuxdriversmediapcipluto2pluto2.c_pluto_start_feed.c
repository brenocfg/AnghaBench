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
struct pluto {int /*<<< orphan*/  full_ts_users; int /*<<< orphan*/  users; } ;
struct dvb_demux_feed {int pid; scalar_t__ index; } ;

/* Variables and functions */
 scalar_t__ NHWFILTERS ; 
 int PID0_AFIL ; 
 int PID0_NOFIL ; 
 int PIDn_ENP ; 
 int PIDn_PID ; 
 int /*<<< orphan*/  REG_PIDn (scalar_t__) ; 
 struct pluto* feed_to_pluto (struct dvb_demux_feed*) ; 
 int /*<<< orphan*/  pluto_rw (struct pluto*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pluto_start_feed(struct dvb_demux_feed *f)
{
	struct pluto *pluto = feed_to_pluto(f);

	/* enable PID filtering */
	if (pluto->users++ == 0)
		pluto_rw(pluto, REG_PIDn(0), PID0_AFIL | PID0_NOFIL, 0);

	if ((f->pid < 0x2000) && (f->index < NHWFILTERS))
		pluto_rw(pluto, REG_PIDn(f->index), PIDn_ENP | PIDn_PID, PIDn_ENP | f->pid);
	else if (pluto->full_ts_users++ == 0)
		pluto_rw(pluto, REG_PIDn(0), PID0_NOFIL, PID0_NOFIL);

	return 0;
}