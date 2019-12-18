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
struct netup_hw_pid_filter {int /*<<< orphan*/  (* stop_feed ) (struct dvb_demux_feed*) ;int /*<<< orphan*/  (* start_feed ) (struct dvb_demux_feed*) ;} ;
struct fpga_internal {struct netup_hw_pid_filter** pid_filt; } ;
struct fpga_inode {struct fpga_internal* internal; } ;
struct dvb_demux_feed {int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  altera_pid_control (struct netup_hw_pid_filter*,int,int) ; 
 int /*<<< orphan*/  altera_toggle_fullts_streaming (struct netup_hw_pid_filter*,int,int) ; 
 struct fpga_inode* find_dinode (void*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_demux_feed*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_demux_feed*) ; 

__attribute__((used)) static int altera_pid_feed_control(void *demux_dev, int filt_nr,
		struct dvb_demux_feed *feed, int onoff)
{
	struct fpga_inode *temp_int = find_dinode(demux_dev);
	struct fpga_internal *inter = temp_int->internal;
	struct netup_hw_pid_filter *pid_filt = inter->pid_filt[filt_nr - 1];

	altera_pid_control(pid_filt, feed->pid, onoff ? 0 : 1);
	/* call old feed proc's */
	if (onoff)
		pid_filt->start_feed(feed);
	else
		pid_filt->stop_feed(feed);

	if (feed->pid == 0x2000)
		altera_toggle_fullts_streaming(pid_filt, filt_nr,
						onoff ? 0 : 1);

	return 0;
}