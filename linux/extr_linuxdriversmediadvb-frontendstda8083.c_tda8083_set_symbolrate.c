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
typedef  int u32 ;
struct tda8083_state {int dummy; } ;
typedef  int ratio ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  tda8083_writereg (struct tda8083_state*,int,int) ; 

__attribute__((used)) static int tda8083_set_symbolrate (struct tda8083_state* state, u32 srate)
{
	u32 ratio;
	u32 tmp;
	u8 filter;

	if (srate > 32000000)
		srate = 32000000;
	if (srate < 500000)
		srate = 500000;

	filter = 0;
	if (srate < 24000000)
		filter = 2;
	if (srate < 16000000)
		filter = 3;

	tmp = 31250 << 16;
	ratio = tmp / srate;

	tmp = (tmp % srate) << 8;
	ratio = (ratio << 8) + tmp / srate;

	tmp = (tmp % srate) << 8;
	ratio = (ratio << 8) + tmp / srate;

	dprintk("tda8083: ratio == %08x\n", (unsigned int) ratio);

	tda8083_writereg (state, 0x05, filter);
	tda8083_writereg (state, 0x02, (ratio >> 16) & 0xff);
	tda8083_writereg (state, 0x03, (ratio >>  8) & 0xff);
	tda8083_writereg (state, 0x04, (ratio      ) & 0xff);

	tda8083_writereg (state, 0x00, 0x3c);
	tda8083_writereg (state, 0x00, 0x04);

	return 1;
}