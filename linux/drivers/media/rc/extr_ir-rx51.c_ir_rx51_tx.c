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
struct rc_dev {struct ir_rx51* priv; } ;
struct ir_rx51 {int* wbuf; int wbuf_index; int /*<<< orphan*/  wqueue; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  US_TO_NS (int) ; 
 unsigned int WBUF_LEN ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timing_params (struct ir_rx51*) ; 
 int /*<<< orphan*/  ir_rx51_on (struct ir_rx51*) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ir_rx51_tx(struct rc_dev *dev, unsigned int *buffer,
		      unsigned int count)
{
	struct ir_rx51 *ir_rx51 = dev->priv;

	if (count > WBUF_LEN)
		return -EINVAL;

	memcpy(ir_rx51->wbuf, buffer, count * sizeof(unsigned int));

	/* Wait any pending transfers to finish */
	wait_event_interruptible(ir_rx51->wqueue, ir_rx51->wbuf_index < 0);

	init_timing_params(ir_rx51);
	if (count < WBUF_LEN)
		ir_rx51->wbuf[count] = -1; /* Insert termination mark */

	/*
	 * REVISIT: Adjust latency requirements so the device doesn't go in too
	 * deep sleep states with pm_qos_add_request().
	 */

	ir_rx51_on(ir_rx51);
	ir_rx51->wbuf_index = 1;
	hrtimer_start(&ir_rx51->timer,
		      ns_to_ktime(US_TO_NS(ir_rx51->wbuf[0])),
		      HRTIMER_MODE_REL);
	/*
	 * Don't return back to the userspace until the transfer has
	 * finished
	 */
	wait_event_interruptible(ir_rx51->wqueue, ir_rx51->wbuf_index < 0);

	/* REVISIT: Remove pm_qos constraint, we can sleep again */

	return count;
}