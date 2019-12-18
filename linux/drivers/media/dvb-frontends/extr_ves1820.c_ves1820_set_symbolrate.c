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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct ves1820_state {TYPE_1__* config; } ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_2__ {int xin; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int* ves1820_inittab ; 
 int /*<<< orphan*/  ves1820_writereg (struct ves1820_state*,int,int) ; 

__attribute__((used)) static int ves1820_set_symbolrate(struct ves1820_state *state, u32 symbolrate)
{
	s32 BDR;
	s32 BDRI;
	s16 SFIL = 0;
	u16 NDEC = 0;
	u32 ratio;
	u32 fin;
	u32 tmp;
	u64 fptmp;
	u64 fpxin;

	if (symbolrate > state->config->xin / 2)
		symbolrate = state->config->xin / 2;

	if (symbolrate < 500000)
		symbolrate = 500000;

	if (symbolrate < state->config->xin / 16)
		NDEC = 1;
	if (symbolrate < state->config->xin / 32)
		NDEC = 2;
	if (symbolrate < state->config->xin / 64)
		NDEC = 3;

	/* yeuch! */
	fpxin = state->config->xin * 10ULL;
	fptmp = fpxin; do_div(fptmp, 123);
	if (symbolrate < fptmp)
		SFIL = 1;
	fptmp = fpxin; do_div(fptmp, 160);
	if (symbolrate < fptmp)
		SFIL = 0;
	fptmp = fpxin; do_div(fptmp, 246);
	if (symbolrate < fptmp)
		SFIL = 1;
	fptmp = fpxin; do_div(fptmp, 320);
	if (symbolrate < fptmp)
		SFIL = 0;
	fptmp = fpxin; do_div(fptmp, 492);
	if (symbolrate < fptmp)
		SFIL = 1;
	fptmp = fpxin; do_div(fptmp, 640);
	if (symbolrate < fptmp)
		SFIL = 0;
	fptmp = fpxin; do_div(fptmp, 984);
	if (symbolrate < fptmp)
		SFIL = 1;

	fin = state->config->xin >> 4;
	symbolrate <<= NDEC;
	ratio = (symbolrate << 4) / fin;
	tmp = ((symbolrate << 4) % fin) << 8;
	ratio = (ratio << 8) + tmp / fin;
	tmp = (tmp % fin) << 8;
	ratio = (ratio << 8) + DIV_ROUND_CLOSEST(tmp, fin);

	BDR = ratio;
	BDRI = (((state->config->xin << 5) / symbolrate) + 1) / 2;

	if (BDRI > 0xFF)
		BDRI = 0xFF;

	SFIL = (SFIL << 4) | ves1820_inittab[0x0E];

	NDEC = (NDEC << 6) | ves1820_inittab[0x03];

	ves1820_writereg(state, 0x03, NDEC);
	ves1820_writereg(state, 0x0a, BDR & 0xff);
	ves1820_writereg(state, 0x0b, (BDR >> 8) & 0xff);
	ves1820_writereg(state, 0x0c, (BDR >> 16) & 0x3f);

	ves1820_writereg(state, 0x0d, BDRI);
	ves1820_writereg(state, 0x0e, SFIL);

	return 0;
}