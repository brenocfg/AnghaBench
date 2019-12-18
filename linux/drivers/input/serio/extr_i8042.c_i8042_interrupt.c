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
struct serio {int dummy; } ;
struct i8042_port {int /*<<< orphan*/  driver_bound; struct serio* serio; scalar_t__ exists; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HZ ; 
 unsigned int I8042_AUX_PORT_NO ; 
 unsigned int I8042_KBD_PORT_NO ; 
 unsigned char I8042_MUX_PORT_NO ; 
 unsigned char I8042_STR_AUXDATA ; 
 unsigned char I8042_STR_MUXERR ; 
 unsigned char I8042_STR_OBF ; 
 unsigned char I8042_STR_PARITY ; 
 unsigned char I8042_STR_TIMEOUT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 unsigned int SERIO_PARITY ; 
 unsigned int SERIO_TIMEOUT ; 
 int /*<<< orphan*/  dbg (char*,unsigned char,...) ; 
 int /*<<< orphan*/  filter_dbg (int /*<<< orphan*/ ,unsigned char,char*,unsigned int,int,char*,char*) ; 
 int i8042_filter (unsigned char,unsigned char,struct serio*) ; 
 int /*<<< orphan*/  i8042_lock ; 
 scalar_t__ i8042_mux_present ; 
 int /*<<< orphan*/  i8042_notimeout ; 
 struct i8042_port* i8042_ports ; 
 unsigned char i8042_read_data () ; 
 unsigned char i8042_read_status () ; 
 unsigned long jiffies ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_interrupt (struct serio*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_before (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (unsigned char) ; 

__attribute__((used)) static irqreturn_t i8042_interrupt(int irq, void *dev_id)
{
	struct i8042_port *port;
	struct serio *serio;
	unsigned long flags;
	unsigned char str, data;
	unsigned int dfl;
	unsigned int port_no;
	bool filtered;
	int ret = 1;

	spin_lock_irqsave(&i8042_lock, flags);

	str = i8042_read_status();
	if (unlikely(~str & I8042_STR_OBF)) {
		spin_unlock_irqrestore(&i8042_lock, flags);
		if (irq)
			dbg("Interrupt %d, without any data\n", irq);
		ret = 0;
		goto out;
	}

	data = i8042_read_data();

	if (i8042_mux_present && (str & I8042_STR_AUXDATA)) {
		static unsigned long last_transmit;
		static unsigned char last_str;

		dfl = 0;
		if (str & I8042_STR_MUXERR) {
			dbg("MUX error, status is %02x, data is %02x\n",
			    str, data);
/*
 * When MUXERR condition is signalled the data register can only contain
 * 0xfd, 0xfe or 0xff if implementation follows the spec. Unfortunately
 * it is not always the case. Some KBCs also report 0xfc when there is
 * nothing connected to the port while others sometimes get confused which
 * port the data came from and signal error leaving the data intact. They
 * _do not_ revert to legacy mode (actually I've never seen KBC reverting
 * to legacy mode yet, when we see one we'll add proper handling).
 * Anyway, we process 0xfc, 0xfd, 0xfe and 0xff as timeouts, and for the
 * rest assume that the data came from the same serio last byte
 * was transmitted (if transmission happened not too long ago).
 */

			switch (data) {
				default:
					if (time_before(jiffies, last_transmit + HZ/10)) {
						str = last_str;
						break;
					}
					/* fall through - report timeout */
				case 0xfc:
				case 0xfd:
				case 0xfe: dfl = SERIO_TIMEOUT; data = 0xfe; break;
				case 0xff: dfl = SERIO_PARITY;  data = 0xfe; break;
			}
		}

		port_no = I8042_MUX_PORT_NO + ((str >> 6) & 3);
		last_str = str;
		last_transmit = jiffies;
	} else {

		dfl = ((str & I8042_STR_PARITY) ? SERIO_PARITY : 0) |
		      ((str & I8042_STR_TIMEOUT && !i8042_notimeout) ? SERIO_TIMEOUT : 0);

		port_no = (str & I8042_STR_AUXDATA) ?
				I8042_AUX_PORT_NO : I8042_KBD_PORT_NO;
	}

	port = &i8042_ports[port_no];
	serio = port->exists ? port->serio : NULL;

	filter_dbg(port->driver_bound, data, "<- i8042 (interrupt, %d, %d%s%s)\n",
		   port_no, irq,
		   dfl & SERIO_PARITY ? ", bad parity" : "",
		   dfl & SERIO_TIMEOUT ? ", timeout" : "");

	filtered = i8042_filter(data, str, serio);

	spin_unlock_irqrestore(&i8042_lock, flags);

	if (likely(serio && !filtered))
		serio_interrupt(serio, data, dfl);

 out:
	return IRQ_RETVAL(ret);
}