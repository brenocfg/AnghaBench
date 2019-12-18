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
typedef  int word ;
typedef  int u16 ;
struct i2c_msg {int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int dib7090p_rw_on_apb (struct i2c_adapter*,struct i2c_msg*,int,int) ; 
 struct dib7000p_state* i2c_get_adapdata (struct i2c_adapter*) ; 
 int w7090p_tuner_rw_serpar (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int dib7090_tuner_xfer(struct i2c_adapter *i2c_adap, struct i2c_msg msg[], int num)
{
	struct dib7000p_state *state = i2c_get_adapdata(i2c_adap);

	u16 apb_address = 0, word;
	int i = 0;
	switch (msg[0].buf[0]) {
	case 0x12:
		apb_address = 1920;
		break;
	case 0x14:
		apb_address = 1921;
		break;
	case 0x24:
		apb_address = 1922;
		break;
	case 0x1a:
		apb_address = 1923;
		break;
	case 0x22:
		apb_address = 1924;
		break;
	case 0x33:
		apb_address = 1926;
		break;
	case 0x34:
		apb_address = 1927;
		break;
	case 0x35:
		apb_address = 1928;
		break;
	case 0x36:
		apb_address = 1929;
		break;
	case 0x37:
		apb_address = 1930;
		break;
	case 0x38:
		apb_address = 1931;
		break;
	case 0x39:
		apb_address = 1932;
		break;
	case 0x2a:
		apb_address = 1935;
		break;
	case 0x2b:
		apb_address = 1936;
		break;
	case 0x2c:
		apb_address = 1937;
		break;
	case 0x2d:
		apb_address = 1938;
		break;
	case 0x2e:
		apb_address = 1939;
		break;
	case 0x2f:
		apb_address = 1940;
		break;
	case 0x30:
		apb_address = 1941;
		break;
	case 0x31:
		apb_address = 1942;
		break;
	case 0x32:
		apb_address = 1943;
		break;
	case 0x3e:
		apb_address = 1944;
		break;
	case 0x3f:
		apb_address = 1945;
		break;
	case 0x40:
		apb_address = 1948;
		break;
	case 0x25:
		apb_address = 914;
		break;
	case 0x26:
		apb_address = 915;
		break;
	case 0x27:
		apb_address = 917;
		break;
	case 0x28:
		apb_address = 916;
		break;
	case 0x1d:
		i = ((dib7000p_read_word(state, 72) >> 12) & 0x3);
		word = dib7000p_read_word(state, 384 + i);
		msg[1].buf[0] = (word >> 8) & 0xff;
		msg[1].buf[1] = (word) & 0xff;
		return num;
	case 0x1f:
		if (num == 1) {	/* write */
			word = (u16) ((msg[0].buf[1] << 8) | msg[0].buf[2]);
			word &= 0x3;
			word = (dib7000p_read_word(state, 72) & ~(3 << 12)) | (word << 12);
			dib7000p_write_word(state, 72, word);	/* Set the proper input */
			return num;
		}
	}

	if (apb_address != 0)	/* R/W access via APB */
		return dib7090p_rw_on_apb(i2c_adap, msg, num, apb_address);
	else			/* R/W access via SERPAR  */
		return w7090p_tuner_rw_serpar(i2c_adap, msg, num);

	return 0;
}