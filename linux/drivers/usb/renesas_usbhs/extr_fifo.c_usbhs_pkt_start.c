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
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSF_PKT_PREPARE ; 
 int /*<<< orphan*/  usbhsf_pkt_handler (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 

void usbhs_pkt_start(struct usbhs_pipe *pipe)
{
	usbhsf_pkt_handler(pipe, USBHSF_PKT_PREPARE);
}