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
struct gc {TYPE_1__* pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int GC_N64_CLOCK ; 
 int GC_N64_DELAY ; 
 int GC_N64_LENGTH ; 
 int /*<<< orphan*/  GC_N64_OUT ; 
 int GC_N64_POWER_R ; 
 int /*<<< orphan*/  GC_N64_REQUEST_DATA ; 
 int /*<<< orphan*/  gc_n64_send_command (struct gc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_n64_send_stop_bit (struct gc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned char parport_read_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gc_n64_read_packet(struct gc *gc, unsigned char *data)
{
	int i;
	unsigned long flags;

/*
 * Request the pad to transmit data
 */

	local_irq_save(flags);
	gc_n64_send_command(gc, GC_N64_REQUEST_DATA, GC_N64_OUT);
	gc_n64_send_stop_bit(gc, GC_N64_OUT);
	local_irq_restore(flags);

/*
 * Wait for the pad response to be loaded into the 33-bit register
 * of the adapter.
 */

	udelay(GC_N64_DELAY);

/*
 * Grab data (ignoring the last bit, which is a stop bit)
 */

	for (i = 0; i < GC_N64_LENGTH; i++) {
		parport_write_data(gc->pd->port, GC_N64_POWER_R);
		udelay(2);
		data[i] = parport_read_status(gc->pd->port);
		parport_write_data(gc->pd->port, GC_N64_POWER_R | GC_N64_CLOCK);
	 }

/*
 * We must wait 200 ms here for the controller to reinitialize before
 * the next read request. No worries as long as gc_read is polled less
 * frequently than this.
 */

}