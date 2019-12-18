#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iguanair {int /*<<< orphan*/  completion; TYPE_1__* urb_out; } ;
struct TYPE_2__ {unsigned int transfer_buffer_length; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iguanair_send(struct iguanair *ir, unsigned size)
{
	int rc;

	reinit_completion(&ir->completion);

	ir->urb_out->transfer_buffer_length = size;
	rc = usb_submit_urb(ir->urb_out, GFP_KERNEL);
	if (rc)
		return rc;

	if (wait_for_completion_timeout(&ir->completion, TIMEOUT) == 0)
		return -ETIMEDOUT;

	return rc;
}