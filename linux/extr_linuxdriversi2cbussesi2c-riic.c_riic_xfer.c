#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct riic_dev {int err; int is_last; int /*<<< orphan*/  clk; TYPE_1__ adapter; int /*<<< orphan*/  msg_done; scalar_t__ base; struct i2c_msg* msg; int /*<<< orphan*/  buf; int /*<<< orphan*/  bytes_left; } ;
struct i2c_msg {int /*<<< orphan*/  buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int ICCR2_BBSY ; 
 int ICCR2_RS ; 
 int ICCR2_ST ; 
 int ICIER_NAKIE ; 
 int ICIER_TIE ; 
 scalar_t__ RIIC_ICCR2 ; 
 scalar_t__ RIIC_ICIER ; 
 scalar_t__ RIIC_ICSR2 ; 
 int /*<<< orphan*/  RIIC_INIT_MSG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct riic_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int riic_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[], int num)
{
	struct riic_dev *riic = i2c_get_adapdata(adap);
	unsigned long time_left;
	int i, ret;
	u8 start_bit;

	ret = clk_prepare_enable(riic->clk);
	if (ret)
		return ret;

	if (readb(riic->base + RIIC_ICCR2) & ICCR2_BBSY) {
		riic->err = -EBUSY;
		goto out;
	}

	reinit_completion(&riic->msg_done);
	riic->err = 0;

	writeb(0, riic->base + RIIC_ICSR2);

	for (i = 0, start_bit = ICCR2_ST; i < num; i++) {
		riic->bytes_left = RIIC_INIT_MSG;
		riic->buf = msgs[i].buf;
		riic->msg = &msgs[i];
		riic->is_last = (i == num - 1);

		writeb(ICIER_NAKIE | ICIER_TIE, riic->base + RIIC_ICIER);

		writeb(start_bit, riic->base + RIIC_ICCR2);

		time_left = wait_for_completion_timeout(&riic->msg_done, riic->adapter.timeout);
		if (time_left == 0)
			riic->err = -ETIMEDOUT;

		if (riic->err)
			break;

		start_bit = ICCR2_RS;
	}

 out:
	clk_disable_unprepare(riic->clk);

	return riic->err ?: num;
}