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
typedef  int u8 ;
typedef  int u16 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ output_mpeg2_in_188_bytes; } ;
struct dib8000_state {int output_mode; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_ON_DIBTX ; 
 int /*<<< orphan*/  DEMOUT_ON_HOSTBUS ; 
 int /*<<< orphan*/  DIBTX_ON_HOSTBUS ; 
 int /*<<< orphan*/  DIV_ON_DIBTX ; 
 int /*<<< orphan*/  MPEG_ON_HOSTBUS ; 
#define  OUTMODE_ANALOG_ADC 134 
#define  OUTMODE_DIVERSITY 133 
#define  OUTMODE_HIGH_Z 132 
#define  OUTMODE_MPEG2_FIFO 131 
#define  OUTMODE_MPEG2_PAR_CONT_CLK 130 
#define  OUTMODE_MPEG2_PAR_GATED_CLK 129 
#define  OUTMODE_MPEG2_SERIAL 128 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dib8096p_configMpegMux (struct dib8000_state*,int,int,int) ; 
 int /*<<< orphan*/  dib8096p_host_bus_drive (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8096p_setDibTxMux (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8096p_setHostBusMux (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static int dib8096p_set_output_mode(struct dvb_frontend *fe, int mode)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 outreg, smo_mode, fifo_threshold;
	u8 prefer_mpeg_mux_use = 1;
	int ret = 0;

	state->output_mode = mode;
	dib8096p_host_bus_drive(state, 1);

	fifo_threshold = 1792;
	smo_mode = (dib8000_read_word(state, 299) & 0x0050) | (1 << 1);
	outreg   = dib8000_read_word(state, 1286) &
		~((1 << 10) | (0x7 << 6) | (1 << 1));

	switch (mode) {
	case OUTMODE_HIGH_Z:
			outreg = 0;
			break;

	case OUTMODE_MPEG2_SERIAL:
			if (prefer_mpeg_mux_use) {
				dprintk("dib8096P setting output mode TS_SERIAL using Mpeg Mux\n");
				dib8096p_configMpegMux(state, 3, 1, 1);
				dib8096p_setHostBusMux(state, MPEG_ON_HOSTBUS);
			} else {/* Use Smooth block */
				dprintk("dib8096P setting output mode TS_SERIAL using Smooth bloc\n");
				dib8096p_setHostBusMux(state,
						DEMOUT_ON_HOSTBUS);
				outreg |= (2 << 6) | (0 << 1);
			}
			break;

	case OUTMODE_MPEG2_PAR_GATED_CLK:
			if (prefer_mpeg_mux_use) {
				dprintk("dib8096P setting output mode TS_PARALLEL_GATED using Mpeg Mux\n");
				dib8096p_configMpegMux(state, 2, 0, 0);
				dib8096p_setHostBusMux(state, MPEG_ON_HOSTBUS);
			} else { /* Use Smooth block */
				dprintk("dib8096P setting output mode TS_PARALLEL_GATED using Smooth block\n");
				dib8096p_setHostBusMux(state,
						DEMOUT_ON_HOSTBUS);
				outreg |= (0 << 6);
			}
			break;

	case OUTMODE_MPEG2_PAR_CONT_CLK: /* Using Smooth block only */
			dprintk("dib8096P setting output mode TS_PARALLEL_CONT using Smooth block\n");
			dib8096p_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outreg |= (1 << 6);
			break;

	case OUTMODE_MPEG2_FIFO:
			/* Using Smooth block because not supported
			   by new Mpeg Mux bloc */
			dprintk("dib8096P setting output mode TS_FIFO using Smooth block\n");
			dib8096p_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outreg |= (5 << 6);
			smo_mode |= (3 << 1);
			fifo_threshold = 512;
			break;

	case OUTMODE_DIVERSITY:
			dprintk("dib8096P setting output mode MODE_DIVERSITY\n");
			dib8096p_setDibTxMux(state, DIV_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
			break;

	case OUTMODE_ANALOG_ADC:
			dprintk("dib8096P setting output mode MODE_ANALOG_ADC\n");
			dib8096p_setDibTxMux(state, ADC_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
			break;
	}

	if (mode != OUTMODE_HIGH_Z)
		outreg |= (1<<10);

	dprintk("output_mpeg2_in_188_bytes = %d\n",
			state->cfg.output_mpeg2_in_188_bytes);
	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	ret |= dib8000_write_word(state, 299, smo_mode);
	/* synchronous fread */
	ret |= dib8000_write_word(state, 299 + 1, fifo_threshold);
	ret |= dib8000_write_word(state, 1286, outreg);

	return ret;
}