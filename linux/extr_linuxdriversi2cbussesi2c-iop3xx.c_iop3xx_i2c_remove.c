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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct i2c_algo_iop3xx_data {scalar_t__ ioaddr; scalar_t__ algo_data; } ;
struct i2c_adapter {scalar_t__ ioaddr; scalar_t__ algo_data; } ;

/* Variables and functions */
 scalar_t__ CR_OFFSET ; 
 int /*<<< orphan*/  IOP3XX_I2C_IO_SIZE ; 
 unsigned long IOP3XX_ICR_ALD_IE ; 
 unsigned long IOP3XX_ICR_BERR_IE ; 
 unsigned long IOP3XX_ICR_RXFULL_IE ; 
 unsigned long IOP3XX_ICR_TXEMPTY_IE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct i2c_algo_iop3xx_data*) ; 
 struct i2c_algo_iop3xx_data* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iop3xx_i2c_remove(struct platform_device *pdev)
{
	struct i2c_adapter *padapter = platform_get_drvdata(pdev);
	struct i2c_algo_iop3xx_data *adapter_data =
		(struct i2c_algo_iop3xx_data *)padapter->algo_data;
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	unsigned long cr = __raw_readl(adapter_data->ioaddr + CR_OFFSET);

	/*
	 * Disable the actual HW unit
	 */
	cr &= ~(IOP3XX_ICR_ALD_IE | IOP3XX_ICR_BERR_IE |
		IOP3XX_ICR_RXFULL_IE | IOP3XX_ICR_TXEMPTY_IE);
	__raw_writel(cr, adapter_data->ioaddr + CR_OFFSET);

	iounmap(adapter_data->ioaddr);
	release_mem_region(res->start, IOP3XX_I2C_IO_SIZE);
	kfree(adapter_data);
	kfree(padapter);

	return 0;
}