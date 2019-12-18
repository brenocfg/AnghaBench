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
struct tda998x_priv {int wq_edid_wait; int /*<<< orphan*/  edid_mutex; TYPE_1__* hdmi; int /*<<< orphan*/  wq_edid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ irq; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int INT_FLAGS_2_EDID_BLK_RD ; 
 int /*<<< orphan*/  REG_DDC_ADDR ; 
 int /*<<< orphan*/  REG_DDC_OFFS ; 
 int /*<<< orphan*/  REG_DDC_SEGM ; 
 int /*<<< orphan*/  REG_DDC_SEGM_ADDR ; 
 int /*<<< orphan*/  REG_EDID_CTRL ; 
 int /*<<< orphan*/  REG_EDID_DATA_0 ; 
 int /*<<< orphan*/  REG_INT_FLAGS_2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int reg_read (struct tda998x_priv*,int /*<<< orphan*/ ) ; 
 int reg_read_range (struct tda998x_priv*,int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  reg_write (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_edid_block(void *data, u8 *buf, unsigned int blk, size_t length)
{
	struct tda998x_priv *priv = data;
	u8 offset, segptr;
	int ret, i;

	offset = (blk & 1) ? 128 : 0;
	segptr = blk / 2;

	mutex_lock(&priv->edid_mutex);

	reg_write(priv, REG_DDC_ADDR, 0xa0);
	reg_write(priv, REG_DDC_OFFS, offset);
	reg_write(priv, REG_DDC_SEGM_ADDR, 0x60);
	reg_write(priv, REG_DDC_SEGM, segptr);

	/* enable reading EDID: */
	priv->wq_edid_wait = 1;
	reg_write(priv, REG_EDID_CTRL, 0x1);

	/* flag must be cleared by sw: */
	reg_write(priv, REG_EDID_CTRL, 0x0);

	/* wait for block read to complete: */
	if (priv->hdmi->irq) {
		i = wait_event_timeout(priv->wq_edid,
					!priv->wq_edid_wait,
					msecs_to_jiffies(100));
		if (i < 0) {
			dev_err(&priv->hdmi->dev, "read edid wait err %d\n", i);
			ret = i;
			goto failed;
		}
	} else {
		for (i = 100; i > 0; i--) {
			msleep(1);
			ret = reg_read(priv, REG_INT_FLAGS_2);
			if (ret < 0)
				goto failed;
			if (ret & INT_FLAGS_2_EDID_BLK_RD)
				break;
		}
	}

	if (i == 0) {
		dev_err(&priv->hdmi->dev, "read edid timeout\n");
		ret = -ETIMEDOUT;
		goto failed;
	}

	ret = reg_read_range(priv, REG_EDID_DATA_0, buf, length);
	if (ret != length) {
		dev_err(&priv->hdmi->dev, "failed to read edid block %d: %d\n",
			blk, ret);
		goto failed;
	}

	ret = 0;

 failed:
	mutex_unlock(&priv->edid_mutex);
	return ret;
}