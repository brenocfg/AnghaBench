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
struct dib8000_state {int input_mode_mpeg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dib8096p_enMpegMux (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static void dib8096p_configMpegMux(struct dib8000_state *state,
		u16 pulseWidth, u16 enSerialMode, u16 enSerialClkDiv2)
{
	u16 reg_1287;

	dprintk("Enable Mpeg mux\n");

	dib8096p_enMpegMux(state, 0);

	/* If the input mode is MPEG do not divide the serial clock */
	if ((enSerialMode == 1) && (state->input_mode_mpeg == 1))
		enSerialClkDiv2 = 0;

	reg_1287 = ((pulseWidth & 0x1f) << 3) |
		((enSerialMode & 0x1) << 2) | (enSerialClkDiv2 & 0x1);
	dib8000_write_word(state, 1287, reg_1287);

	dib8096p_enMpegMux(state, 1);
}