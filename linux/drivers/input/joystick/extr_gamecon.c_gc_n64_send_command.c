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
struct parport {int dummy; } ;
struct gc {TYPE_1__* pd; } ;
struct TYPE_2__ {struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC_N64_DWS ; 
 int GC_N64_LENGTH ; 
 unsigned char GC_N64_POWER_W ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,unsigned char) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_n64_send_command(struct gc *gc, unsigned long cmd,
				unsigned char target)
{
	struct parport *port = gc->pd->port;
	int i;

	for (i = 0; i < GC_N64_LENGTH; i++) {
		unsigned char data = (cmd >> i) & 1 ? target : 0;
		parport_write_data(port, GC_N64_POWER_W | data);
		udelay(GC_N64_DWS);
	}
}