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
struct mt312_state {int dummy; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS_BERCNT_H ; 
 int mt312_read (struct mt312_state*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mt312_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct mt312_state *state = fe->demodulator_priv;
	int ret;
	u8 buf[3];

	ret = mt312_read(state, RS_BERCNT_H, buf, 3);
	if (ret < 0)
		return ret;

	*ber = ((buf[0] << 16) | (buf[1] << 8) | buf[2]) * 64;

	return 0;
}