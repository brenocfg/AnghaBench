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
struct spk_synth {int /*<<< orphan*/  long_name; scalar_t__ alive; } ;
struct TYPE_2__ {scalar_t__ port_tts; } ;

/* Variables and functions */
 scalar_t__ NUM_DISABLE_TIMEOUTS ; 
 int SPK_CTS_TIMEOUT ; 
 int SPK_XMITR_TIMEOUT ; 
 scalar_t__ UART_MSR ; 
 int UART_MSR_CTS ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  speakup_start_ttys () ; 
 scalar_t__ spk_serial_tx_busy () ; 
 scalar_t__ timeouts ; 
 int /*<<< orphan*/  udelay (int) ; 

int spk_wait_for_xmitr(struct spk_synth *in_synth)
{
	int tmout = SPK_XMITR_TIMEOUT;

	if ((in_synth->alive) && (timeouts >= NUM_DISABLE_TIMEOUTS)) {
		pr_warn("%s: too many timeouts, deactivating speakup\n",
			in_synth->long_name);
		in_synth->alive = 0;
		/* No synth any more, so nobody will restart TTYs, and we thus
		 * need to do it ourselves.  Now that there is no synth we can
		 * let application flood anyway
		 */
		speakup_start_ttys();
		timeouts = 0;
		return 0;
	}
	while (spk_serial_tx_busy()) {
		if (--tmout == 0) {
			pr_warn("%s: timed out (tx busy)\n",
				in_synth->long_name);
			timeouts++;
			return 0;
		}
		udelay(1);
	}
	tmout = SPK_CTS_TIMEOUT;
	while (!((inb_p(speakup_info.port_tts + UART_MSR)) & UART_MSR_CTS)) {
		/* CTS */
		if (--tmout == 0) {
			timeouts++;
			return 0;
		}
		udelay(1);
	}
	timeouts = 0;
	return 1;
}