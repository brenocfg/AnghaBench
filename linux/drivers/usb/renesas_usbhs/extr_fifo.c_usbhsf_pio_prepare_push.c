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
struct usbhs_pkt {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 scalar_t__ usbhs_pipe_is_running (int /*<<< orphan*/ ) ; 
 int usbhsf_pio_try_push (struct usbhs_pkt*,int*) ; 

__attribute__((used)) static int usbhsf_pio_prepare_push(struct usbhs_pkt *pkt, int *is_done)
{
	if (usbhs_pipe_is_running(pkt->pipe))
		return 0;

	return usbhsf_pio_try_push(pkt, is_done);
}