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
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int revision; scalar_t__ autosearch_state; } ;

/* Variables and functions */
 scalar_t__ AS_SEARCHING_FFT ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib8000_autosearch_irq(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 irq_pending = dib8000_read_word(state, 1284);

	if ((state->revision >= 0x8002) &&
	    (state->autosearch_state == AS_SEARCHING_FFT)) {
		if (irq_pending & 0x1) {
			dprintk("dib8000_autosearch_irq: max correlation result available\n");
			return 3;
		}
	} else {
		if (irq_pending & 0x1) {	/* failed */
			dprintk("dib8000_autosearch_irq failed\n");
			return 1;
		}

		if (irq_pending & 0x2) {	/* succeeded */
			dprintk("dib8000_autosearch_irq succeeded\n");
			return 2;
		}
	}

	return 0;		// still pending
}