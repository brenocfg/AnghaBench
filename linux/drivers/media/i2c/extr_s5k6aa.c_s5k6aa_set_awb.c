#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct s5k6aa_ctrls {TYPE_3__* gain_blue; TYPE_2__* gain_green; TYPE_1__* gain_red; } ;
struct s5k6aa {struct s5k6aa_ctrls ctrls; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;
struct TYPE_6__ {int val; } ;
struct TYPE_5__ {int val; } ;
struct TYPE_4__ {int val; } ;

/* Variables and functions */
 int AALG_WB_EN_MASK ; 
 int /*<<< orphan*/  REG_DBG_AUTOALG_EN ; 
 int /*<<< orphan*/  REG_SF_BGAIN ; 
 int /*<<< orphan*/  REG_SF_BGAIN_CHG ; 
 int /*<<< orphan*/  REG_SF_GGAIN ; 
 int /*<<< orphan*/  REG_SF_GGAIN_CHG ; 
 int /*<<< orphan*/  REG_SF_RGAIN ; 
 int /*<<< orphan*/  REG_SF_RGAIN_CHG ; 
 int s5k6aa_read (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 
 int s5k6aa_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k6aa_set_awb(struct s5k6aa *s5k6aa, int awb)
{
	struct i2c_client *c = v4l2_get_subdevdata(&s5k6aa->sd);
	struct s5k6aa_ctrls *ctrls = &s5k6aa->ctrls;
	u16 reg;

	int ret = s5k6aa_read(c, REG_DBG_AUTOALG_EN, &reg);

	if (!ret && !awb) {
		ret = s5k6aa_write(c, REG_SF_RGAIN, ctrls->gain_red->val);
		if (!ret)
			ret = s5k6aa_write(c, REG_SF_RGAIN_CHG, 1);
		if (ret)
			return ret;

		ret = s5k6aa_write(c, REG_SF_GGAIN, ctrls->gain_green->val);
		if (!ret)
			ret = s5k6aa_write(c, REG_SF_GGAIN_CHG, 1);
		if (ret)
			return ret;

		ret = s5k6aa_write(c, REG_SF_BGAIN, ctrls->gain_blue->val);
		if (!ret)
			ret = s5k6aa_write(c, REG_SF_BGAIN_CHG, 1);
	}
	if (!ret) {
		reg = awb ? reg | AALG_WB_EN_MASK : reg & ~AALG_WB_EN_MASK;
		ret = s5k6aa_write(c, REG_DBG_AUTOALG_EN, reg);
	}

	return ret;
}