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
struct octeon_hcd {int dummy; } ;
struct cvmx_usb_pipe {int /*<<< orphan*/  node; int /*<<< orphan*/  transactions; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfree (struct cvmx_usb_pipe*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cvmx_usb_close_pipe(struct octeon_hcd *usb,
			       struct cvmx_usb_pipe *pipe)
{
	/* Fail if the pipe has pending transactions */
	if (!list_empty(&pipe->transactions))
		return -EBUSY;

	list_del(&pipe->node);
	kfree(pipe);

	return 0;
}