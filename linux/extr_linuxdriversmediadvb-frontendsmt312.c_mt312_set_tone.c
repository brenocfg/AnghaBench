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
struct mt312_state {int dummy; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DISEQC_MODE ; 
 int EINVAL ; 
 int const SEC_TONE_OFF ; 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 
 int mt312_writereg (struct mt312_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt312_set_tone(struct dvb_frontend *fe,
			  const enum fe_sec_tone_mode t)
{
	struct mt312_state *state = fe->demodulator_priv;
	const u8 tone_tab[2] = { 0x01, 0x00 };

	int ret;
	u8 diseqc_mode;

	if (t > SEC_TONE_OFF)
		return -EINVAL;

	ret = mt312_readreg(state, DISEQC_MODE, &diseqc_mode);
	if (ret < 0)
		return ret;

	ret = mt312_writereg(state, DISEQC_MODE,
			     (diseqc_mode & 0x40) | tone_tab[t]);
	if (ret < 0)
		return ret;

	return 0;
}