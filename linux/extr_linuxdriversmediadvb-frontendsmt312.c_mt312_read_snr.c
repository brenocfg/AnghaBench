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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  M_SNR_H ; 
 int mt312_read (struct mt312_state*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mt312_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct mt312_state *state = fe->demodulator_priv;
	int ret;
	u8 buf[2];

	ret = mt312_read(state, M_SNR_H, buf, sizeof(buf));
	if (ret < 0)
		return ret;

	*snr = 0xFFFF - ((((buf[0] & 0x7f) << 8) | buf[1]) << 1);

	return 0;
}