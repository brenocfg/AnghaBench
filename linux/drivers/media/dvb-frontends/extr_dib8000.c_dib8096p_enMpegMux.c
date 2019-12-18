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
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static void dib8096p_enMpegMux(struct dib8000_state *state, int onoff)
{
	u16 reg_1287;

	reg_1287 = dib8000_read_word(state, 1287);

	switch (onoff) {
	case 1:
			reg_1287 &= ~(1 << 8);
			break;
	case 0:
			reg_1287 |= (1 << 8);
			break;
	}

	dib8000_write_word(state, 1287, reg_1287);
}