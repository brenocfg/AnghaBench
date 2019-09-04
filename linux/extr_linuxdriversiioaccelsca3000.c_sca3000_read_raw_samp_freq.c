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
struct sca3000_state {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_CTRL_SEL_OUT_CTRL ; 
#define  SCA3000_REG_OUT_CTRL_BUF_DIV_2 129 
#define  SCA3000_REG_OUT_CTRL_BUF_DIV_4 128 
 int SCA3000_REG_OUT_CTRL_BUF_DIV_MASK ; 
 int __sca3000_get_base_freq (struct sca3000_state*,int /*<<< orphan*/ ,int*) ; 
 int sca3000_read_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sca3000_read_raw_samp_freq(struct sca3000_state *st, int *val)
{
	int ret;

	ret = __sca3000_get_base_freq(st, st->info, val);
	if (ret)
		return ret;

	ret = sca3000_read_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL);
	if (ret < 0)
		return ret;

	if (*val > 0) {
		ret &= SCA3000_REG_OUT_CTRL_BUF_DIV_MASK;
		switch (ret) {
		case SCA3000_REG_OUT_CTRL_BUF_DIV_2:
			*val /= 2;
			break;
		case SCA3000_REG_OUT_CTRL_BUF_DIV_4:
			*val /= 4;
			break;
		}
	}

	return 0;
}