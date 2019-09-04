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
struct mtk_i2c {scalar_t__ speed_hz; int ignore_restart_irq; int /*<<< orphan*/  op; scalar_t__ auto_restart; int /*<<< orphan*/  dev; TYPE_1__* dev_comp; } ;
struct i2c_msg {int flags; scalar_t__ addr; int /*<<< orphan*/  buf; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ auto_restart; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2C_MASTER_RD ; 
 int /*<<< orphan*/  I2C_MASTER_WR ; 
 int /*<<< orphan*/  I2C_MASTER_WRRD ; 
 int I2C_M_RD ; 
 scalar_t__ MAX_FS_MODE_SPEED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct mtk_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mtk_i2c_clock_disable (struct mtk_i2c*) ; 
 int mtk_i2c_clock_enable (struct mtk_i2c*) ; 
 int mtk_i2c_do_transfer (struct mtk_i2c*,struct i2c_msg*,int,int) ; 

__attribute__((used)) static int mtk_i2c_transfer(struct i2c_adapter *adap,
			    struct i2c_msg msgs[], int num)
{
	int ret;
	int left_num = num;
	struct mtk_i2c *i2c = i2c_get_adapdata(adap);

	ret = mtk_i2c_clock_enable(i2c);
	if (ret)
		return ret;

	i2c->auto_restart = i2c->dev_comp->auto_restart;

	/* checking if we can skip restart and optimize using WRRD mode */
	if (i2c->auto_restart && num == 2) {
		if (!(msgs[0].flags & I2C_M_RD) && (msgs[1].flags & I2C_M_RD) &&
		    msgs[0].addr == msgs[1].addr) {
			i2c->auto_restart = 0;
		}
	}

	if (i2c->auto_restart && num >= 2 && i2c->speed_hz > MAX_FS_MODE_SPEED)
		/* ignore the first restart irq after the master code,
		 * otherwise the first transfer will be discarded.
		 */
		i2c->ignore_restart_irq = true;
	else
		i2c->ignore_restart_irq = false;

	while (left_num--) {
		if (!msgs->buf) {
			dev_dbg(i2c->dev, "data buffer is NULL.\n");
			ret = -EINVAL;
			goto err_exit;
		}

		if (msgs->flags & I2C_M_RD)
			i2c->op = I2C_MASTER_RD;
		else
			i2c->op = I2C_MASTER_WR;

		if (!i2c->auto_restart) {
			if (num > 1) {
				/* combined two messages into one transaction */
				i2c->op = I2C_MASTER_WRRD;
				left_num--;
			}
		}

		/* always use DMA mode. */
		ret = mtk_i2c_do_transfer(i2c, msgs, num, left_num);
		if (ret < 0)
			goto err_exit;

		msgs++;
	}
	/* the return value is number of executed messages */
	ret = num;

err_exit:
	mtk_i2c_clock_disable(i2c);
	return ret;
}