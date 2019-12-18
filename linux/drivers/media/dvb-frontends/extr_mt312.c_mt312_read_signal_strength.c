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
struct mt312_state {int dummy; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_H ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int mt312_read (struct mt312_state*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mt312_read_signal_strength(struct dvb_frontend *fe,
				      u16 *signal_strength)
{
	struct mt312_state *state = fe->demodulator_priv;
	int ret;
	u8 buf[3];
	u16 agc;
	s16 err_db;

	ret = mt312_read(state, AGC_H, buf, sizeof(buf));
	if (ret < 0)
		return ret;

	agc = (buf[0] << 6) | (buf[1] >> 2);
	err_db = (s16) (((buf[1] & 0x03) << 14) | buf[2] << 6) >> 6;

	*signal_strength = agc;

	dprintk("agc=%08x err_db=%hd\n", agc, err_db);

	return 0;
}