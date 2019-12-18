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
typedef  int u8 ;
typedef  int u16 ;
struct dib3000mc_state {int dummy; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 scalar_t__ TRANSMISSION_MODE_8K ; 
 int dib3000mc_read_word (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 
 int* impulse_noise_val ; 

__attribute__((used)) static void dib3000mc_set_impulse_noise(struct dib3000mc_state *state, u8 mode, s16 nfft)
{
	u16 i;
	for (i = 58; i < 87; i++)
		dib3000mc_write_word(state, i, impulse_noise_val[i-58]);

	if (nfft == TRANSMISSION_MODE_8K) {
		dib3000mc_write_word(state, 58, 0x3b);
		dib3000mc_write_word(state, 84, 0x00);
		dib3000mc_write_word(state, 85, 0x8200);
	}

	dib3000mc_write_word(state, 34, 0x1294);
	dib3000mc_write_word(state, 35, 0x1ff8);
	if (mode == 1)
		dib3000mc_write_word(state, 55, dib3000mc_read_word(state, 55) | (1 << 10));
}