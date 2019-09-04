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
union i2c_smbus_data {int byte; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct p2wi {scalar_t__ slave_addr; int status; scalar_t__ regs; int /*<<< orphan*/  complete; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 char I2C_SMBUS_READ ; 
 scalar_t__ P2WI_CTRL ; 
 int P2WI_CTRL_GLOBAL_INT_ENB ; 
 int P2WI_CTRL_START_TRANS ; 
 scalar_t__ P2WI_DADDR0 ; 
 scalar_t__ P2WI_DATA0 ; 
 scalar_t__ P2WI_DLEN ; 
 unsigned long P2WI_DLEN_DATA_LENGTH (int) ; 
 unsigned long P2WI_DLEN_READ ; 
 scalar_t__ P2WI_INTE ; 
 int P2WI_INTS_LOAD_BSY ; 
 int P2WI_INTS_TRANS_ERR ; 
 int P2WI_INTS_TRANS_OVER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct p2wi* i2c_get_adapdata (struct i2c_adapter*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int p2wi_smbus_xfer(struct i2c_adapter *adap, u16 addr,
			   unsigned short flags, char read_write,
			   u8 command, int size, union i2c_smbus_data *data)
{
	struct p2wi *p2wi = i2c_get_adapdata(adap);
	unsigned long dlen = P2WI_DLEN_DATA_LENGTH(1);

	if (p2wi->slave_addr >= 0 && addr != p2wi->slave_addr) {
		dev_err(&adap->dev, "invalid P2WI address\n");
		return -EINVAL;
	}

	if (!data)
		return -EINVAL;

	writel(command, p2wi->regs + P2WI_DADDR0);

	if (read_write == I2C_SMBUS_READ)
		dlen |= P2WI_DLEN_READ;
	else
		writel(data->byte, p2wi->regs + P2WI_DATA0);

	writel(dlen, p2wi->regs + P2WI_DLEN);

	if (readl(p2wi->regs + P2WI_CTRL) & P2WI_CTRL_START_TRANS) {
		dev_err(&adap->dev, "P2WI bus busy\n");
		return -EBUSY;
	}

	reinit_completion(&p2wi->complete);

	writel(P2WI_INTS_LOAD_BSY | P2WI_INTS_TRANS_ERR | P2WI_INTS_TRANS_OVER,
	       p2wi->regs + P2WI_INTE);

	writel(P2WI_CTRL_START_TRANS | P2WI_CTRL_GLOBAL_INT_ENB,
	       p2wi->regs + P2WI_CTRL);

	wait_for_completion(&p2wi->complete);

	if (p2wi->status & P2WI_INTS_LOAD_BSY) {
		dev_err(&adap->dev, "P2WI bus busy\n");
		return -EBUSY;
	}

	if (p2wi->status & P2WI_INTS_TRANS_ERR) {
		dev_err(&adap->dev, "P2WI bus xfer error\n");
		return -ENXIO;
	}

	if (read_write == I2C_SMBUS_READ)
		data->byte = readl(p2wi->regs + P2WI_DATA0);

	return 0;
}