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
typedef  long u32 ;
struct stv0297_state {int dummy; } ;

/* Variables and functions */
 int STV0297_CLOCK_KHZ ; 
 int /*<<< orphan*/  stv0297_writereg (struct stv0297_state*,int,unsigned char) ; 

__attribute__((used)) static void stv0297_set_symbolrate(struct stv0297_state *state, u32 srate)
{
	long tmp;

	tmp = 131072L * srate;	/* 131072 = 2^17  */
	tmp = tmp / (STV0297_CLOCK_KHZ / 4);	/* 1/4 = 2^-2 */
	tmp = tmp * 8192L;	/* 8192 = 2^13 */

	stv0297_writereg(state, 0x55, (unsigned char) (tmp & 0xFF));
	stv0297_writereg(state, 0x56, (unsigned char) (tmp >> 8));
	stv0297_writereg(state, 0x57, (unsigned char) (tmp >> 16));
	stv0297_writereg(state, 0x58, (unsigned char) (tmp >> 24));
}