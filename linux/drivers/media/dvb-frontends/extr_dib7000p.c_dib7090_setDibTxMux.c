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
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
#define  ADC_ON_DIBTX 130 
#define  DIV_ON_DIBTX 129 
#define  MPEG_ON_DIBTX 128 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  dib7090_cfg_DibTx (struct dib7000p_state*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static void dib7090_setDibTxMux(struct dib7000p_state *state, int mode)
{
	u16 reg_1288 = dib7000p_read_word(state, 1288) & ~(0x7 << 7);

	switch (mode) {
	case MPEG_ON_DIBTX:
			dprintk("SET MPEG ON DIBSTREAM TX\n");
			dib7090_cfg_DibTx(state, 8, 5, 0, 0, 0, 0);
			reg_1288 |= (1<<9);
			break;
	case DIV_ON_DIBTX:
			dprintk("SET DIV_OUT ON DIBSTREAM TX\n");
			dib7090_cfg_DibTx(state, 5, 5, 0, 0, 0, 0);
			reg_1288 |= (1<<8);
			break;
	case ADC_ON_DIBTX:
			dprintk("SET ADC_OUT ON DIBSTREAM TX\n");
			dib7090_cfg_DibTx(state, 20, 5, 10, 0, 0, 0);
			reg_1288 |= (1<<7);
			break;
	default:
			break;
	}
	dib7000p_write_word(state, 1288, reg_1288);
}