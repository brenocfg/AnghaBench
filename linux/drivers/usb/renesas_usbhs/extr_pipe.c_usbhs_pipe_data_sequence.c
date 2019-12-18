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
typedef  int u16 ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int SQCLR ; 
 int SQSET ; 
 int /*<<< orphan*/  usbhsp_pipectrl_set (struct usbhs_pipe*,int,int) ; 

void usbhs_pipe_data_sequence(struct usbhs_pipe *pipe, int sequence)
{
	u16 mask = (SQCLR | SQSET);
	u16 val;

	/*
	 * sequence
	 *  0  : data0
	 *  1  : data1
	 *  -1 : no change
	 */
	switch (sequence) {
	case 0:
		val = SQCLR;
		break;
	case 1:
		val = SQSET;
		break;
	default:
		return;
	}

	usbhsp_pipectrl_set(pipe, mask, val);
}