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
struct i2c_msg {int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct dib8000_state {int dummy; } ;
typedef  int read_word ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 struct dib8000_state* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int dib8096p_tuner_read_serpar(struct i2c_adapter *i2c_adap,
		struct i2c_msg msg[], int num)
{
	struct dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_overflow = 1, n_empty = 1;
	u16 i = 1000;
	u16 serpar_num = msg[0].buf[0];
	u16 read_word;

	while (n_overflow == 1 && i) {
		n_overflow = (dib8000_read_word(state, 1984) >> 1) & 0x1;
		i--;
		if (i == 0)
			dprintk("TunerITF: read busy (overflow)\n");
	}
	dib8000_write_word(state, 1985, (0<<6) | (serpar_num&0x3f));

	i = 1000;
	while (n_empty == 1 && i) {
		n_empty = dib8000_read_word(state, 1984)&0x1;
		i--;
		if (i == 0)
			dprintk("TunerITF: read busy (empty)\n");
	}

	read_word = dib8000_read_word(state, 1987);
	msg[1].buf[0] = (read_word >> 8) & 0xff;
	msg[1].buf[1] = (read_word) & 0xff;

	return num;
}