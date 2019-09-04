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
struct lgdt3306a_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*) ; 
 scalar_t__ lg_chkerr (int) ; 
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int,int*) ; 
 int lgdt3306a_soft_reset (struct lgdt3306a_state*) ; 
 int lgdt3306a_write_reg (struct lgdt3306a_state*,int,int) ; 

__attribute__((used)) static int lgdt3306a_set_vsb(struct lgdt3306a_state *state)
{
	u8 val;
	int ret;

	dbg_info("\n");

	/* 0. Spectrum inversion detection manual; spectrum inverted */
	ret = lgdt3306a_read_reg(state, 0x0002, &val);
	val &= 0xf7; /* SPECINVAUTO Off */
	val |= 0x04; /* SPECINV On */
	ret = lgdt3306a_write_reg(state, 0x0002, val);
	if (lg_chkerr(ret))
		goto fail;

	/* 1. Selection of standard mode(0x08=QAM, 0x80=VSB) */
	ret = lgdt3306a_write_reg(state, 0x0008, 0x80);
	if (lg_chkerr(ret))
		goto fail;

	/* 2. Bandwidth mode for VSB(6MHz) */
	ret = lgdt3306a_read_reg(state, 0x0009, &val);
	val &= 0xe3;
	val |= 0x0c; /* STDOPDETTMODE[2:0]=3 */
	ret = lgdt3306a_write_reg(state, 0x0009, val);
	if (lg_chkerr(ret))
		goto fail;

	/* 3. QAM mode detection mode(None) */
	ret = lgdt3306a_read_reg(state, 0x0009, &val);
	val &= 0xfc; /* STDOPDETCMODE[1:0]=0 */
	ret = lgdt3306a_write_reg(state, 0x0009, val);
	if (lg_chkerr(ret))
		goto fail;

	/* 4. ADC sampling frequency rate(2x sampling) */
	ret = lgdt3306a_read_reg(state, 0x000d, &val);
	val &= 0xbf; /* SAMPLING4XFEN=0 */
	ret = lgdt3306a_write_reg(state, 0x000d, val);
	if (lg_chkerr(ret))
		goto fail;

#if 0
	/* FGR - disable any AICC filtering, testing only */

	ret = lgdt3306a_write_reg(state, 0x0024, 0x00);
	if (lg_chkerr(ret))
		goto fail;

	/* AICCFIXFREQ0 NT N-1(Video rejection) */
	ret = lgdt3306a_write_reg(state, 0x002e, 0x00);
	ret = lgdt3306a_write_reg(state, 0x002f, 0x00);
	ret = lgdt3306a_write_reg(state, 0x0030, 0x00);

	/* AICCFIXFREQ1 NT N-1(Audio rejection) */
	ret = lgdt3306a_write_reg(state, 0x002b, 0x00);
	ret = lgdt3306a_write_reg(state, 0x002c, 0x00);
	ret = lgdt3306a_write_reg(state, 0x002d, 0x00);

	/* AICCFIXFREQ2 NT Co-Channel(Video rejection) */
	ret = lgdt3306a_write_reg(state, 0x0028, 0x00);
	ret = lgdt3306a_write_reg(state, 0x0029, 0x00);
	ret = lgdt3306a_write_reg(state, 0x002a, 0x00);

	/* AICCFIXFREQ3 NT Co-Channel(Audio rejection) */
	ret = lgdt3306a_write_reg(state, 0x0025, 0x00);
	ret = lgdt3306a_write_reg(state, 0x0026, 0x00);
	ret = lgdt3306a_write_reg(state, 0x0027, 0x00);

#else
	/* FGR - this works well for HVR-1955,1975 */

	/* 5. AICCOPMODE  NT N-1 Adj. */
	ret = lgdt3306a_write_reg(state, 0x0024, 0x5A);
	if (lg_chkerr(ret))
		goto fail;

	/* AICCFIXFREQ0 NT N-1(Video rejection) */
	ret = lgdt3306a_write_reg(state, 0x002e, 0x5A);
	ret = lgdt3306a_write_reg(state, 0x002f, 0x00);
	ret = lgdt3306a_write_reg(state, 0x0030, 0x00);

	/* AICCFIXFREQ1 NT N-1(Audio rejection) */
	ret = lgdt3306a_write_reg(state, 0x002b, 0x36);
	ret = lgdt3306a_write_reg(state, 0x002c, 0x00);
	ret = lgdt3306a_write_reg(state, 0x002d, 0x00);

	/* AICCFIXFREQ2 NT Co-Channel(Video rejection) */
	ret = lgdt3306a_write_reg(state, 0x0028, 0x2A);
	ret = lgdt3306a_write_reg(state, 0x0029, 0x00);
	ret = lgdt3306a_write_reg(state, 0x002a, 0x00);

	/* AICCFIXFREQ3 NT Co-Channel(Audio rejection) */
	ret = lgdt3306a_write_reg(state, 0x0025, 0x06);
	ret = lgdt3306a_write_reg(state, 0x0026, 0x00);
	ret = lgdt3306a_write_reg(state, 0x0027, 0x00);
#endif

	ret = lgdt3306a_read_reg(state, 0x001e, &val);
	val &= 0x0f;
	val |= 0xa0;
	ret = lgdt3306a_write_reg(state, 0x001e, val);

	ret = lgdt3306a_write_reg(state, 0x0022, 0x08);

	ret = lgdt3306a_write_reg(state, 0x0023, 0xFF);

	ret = lgdt3306a_read_reg(state, 0x211f, &val);
	val &= 0xef;
	ret = lgdt3306a_write_reg(state, 0x211f, val);

	ret = lgdt3306a_write_reg(state, 0x2173, 0x01);

	ret = lgdt3306a_read_reg(state, 0x1061, &val);
	val &= 0xf8;
	val |= 0x04;
	ret = lgdt3306a_write_reg(state, 0x1061, val);

	ret = lgdt3306a_read_reg(state, 0x103d, &val);
	val &= 0xcf;
	ret = lgdt3306a_write_reg(state, 0x103d, val);

	ret = lgdt3306a_write_reg(state, 0x2122, 0x40);

	ret = lgdt3306a_read_reg(state, 0x2141, &val);
	val &= 0x3f;
	ret = lgdt3306a_write_reg(state, 0x2141, val);

	ret = lgdt3306a_read_reg(state, 0x2135, &val);
	val &= 0x0f;
	val |= 0x70;
	ret = lgdt3306a_write_reg(state, 0x2135, val);

	ret = lgdt3306a_read_reg(state, 0x0003, &val);
	val &= 0xf7;
	ret = lgdt3306a_write_reg(state, 0x0003, val);

	ret = lgdt3306a_read_reg(state, 0x001c, &val);
	val &= 0x7f;
	ret = lgdt3306a_write_reg(state, 0x001c, val);

	/* 6. EQ step size */
	ret = lgdt3306a_read_reg(state, 0x2179, &val);
	val &= 0xf8;
	ret = lgdt3306a_write_reg(state, 0x2179, val);

	ret = lgdt3306a_read_reg(state, 0x217a, &val);
	val &= 0xf8;
	ret = lgdt3306a_write_reg(state, 0x217a, val);

	/* 7. Reset */
	ret = lgdt3306a_soft_reset(state);
	if (lg_chkerr(ret))
		goto fail;

	dbg_info("complete\n");
fail:
	return ret;
}