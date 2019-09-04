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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int v4l2_ctrl_poll (struct file*,struct poll_table_struct*) ; 

__poll_t vivid_radio_rx_poll(struct file *file, struct poll_table_struct *wait)
{
	return EPOLLIN | EPOLLRDNORM | v4l2_ctrl_poll(file, wait);
}