#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_master {int mode_bits; int /*<<< orphan*/  setup; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  num_chipselect; } ;
struct TYPE_3__ {int /*<<< orphan*/  txrx_bufs; int /*<<< orphan*/  chipselect; int /*<<< orphan*/  setup_transfer; struct spi_master* master; } ;
struct s3c24xx_spi {scalar_t__ irq; struct spi_master* master; int /*<<< orphan*/  clk; TYPE_1__ bitbang; scalar_t__ set_cs; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; struct s3c2410_spi_info* pdata; int /*<<< orphan*/  done; } ;
struct s3c2410_spi_info {scalar_t__ pin_cs; scalar_t__ set_cs; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  num_cs; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct s3c2410_spi_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int devm_gpio_request (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s3c24xx_spi*) ; 
 int /*<<< orphan*/  gpio_direction_output (scalar_t__,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s3c24xx_spi*) ; 
 int /*<<< orphan*/  s3c24xx_spi_chipsel ; 
 scalar_t__ s3c24xx_spi_gpiocs ; 
 int /*<<< orphan*/  s3c24xx_spi_initfiq (struct s3c24xx_spi*) ; 
 int /*<<< orphan*/  s3c24xx_spi_initialsetup (struct s3c24xx_spi*) ; 
 int /*<<< orphan*/  s3c24xx_spi_irq ; 
 int /*<<< orphan*/  s3c24xx_spi_setup ; 
 int /*<<< orphan*/  s3c24xx_spi_setupxfer ; 
 int /*<<< orphan*/  s3c24xx_spi_txrx ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 int spi_bitbang_start (TYPE_1__*) ; 
 struct s3c24xx_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int s3c24xx_spi_probe(struct platform_device *pdev)
{
	struct s3c2410_spi_info *pdata;
	struct s3c24xx_spi *hw;
	struct spi_master *master;
	int err = 0;

	master = spi_alloc_master(&pdev->dev, sizeof(struct s3c24xx_spi));
	if (master == NULL) {
		dev_err(&pdev->dev, "No memory for spi_master\n");
		return -ENOMEM;
	}

	hw = spi_master_get_devdata(master);

	hw->master = master;
	hw->pdata = pdata = dev_get_platdata(&pdev->dev);
	hw->dev = &pdev->dev;

	if (pdata == NULL) {
		dev_err(&pdev->dev, "No platform data supplied\n");
		err = -ENOENT;
		goto err_no_pdata;
	}

	platform_set_drvdata(pdev, hw);
	init_completion(&hw->done);

	/* initialise fiq handler */

	s3c24xx_spi_initfiq(hw);

	/* setup the master state. */

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;

	master->num_chipselect = hw->pdata->num_cs;
	master->bus_num = pdata->bus_num;
	master->bits_per_word_mask = SPI_BPW_MASK(8);

	/* setup the state for the bitbang driver */

	hw->bitbang.master         = hw->master;
	hw->bitbang.setup_transfer = s3c24xx_spi_setupxfer;
	hw->bitbang.chipselect     = s3c24xx_spi_chipsel;
	hw->bitbang.txrx_bufs      = s3c24xx_spi_txrx;

	hw->master->setup  = s3c24xx_spi_setup;

	dev_dbg(hw->dev, "bitbang at %p\n", &hw->bitbang);

	/* find and map our resources */
	hw->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(hw->regs)) {
		err = PTR_ERR(hw->regs);
		goto err_no_pdata;
	}

	hw->irq = platform_get_irq(pdev, 0);
	if (hw->irq < 0) {
		err = -ENOENT;
		goto err_no_pdata;
	}

	err = devm_request_irq(&pdev->dev, hw->irq, s3c24xx_spi_irq, 0,
				pdev->name, hw);
	if (err) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		goto err_no_pdata;
	}

	hw->clk = devm_clk_get(&pdev->dev, "spi");
	if (IS_ERR(hw->clk)) {
		dev_err(&pdev->dev, "No clock for device\n");
		err = PTR_ERR(hw->clk);
		goto err_no_pdata;
	}

	/* setup any gpio we can */

	if (!pdata->set_cs) {
		if (pdata->pin_cs < 0) {
			dev_err(&pdev->dev, "No chipselect pin\n");
			err = -EINVAL;
			goto err_register;
		}

		err = devm_gpio_request(&pdev->dev, pdata->pin_cs,
					dev_name(&pdev->dev));
		if (err) {
			dev_err(&pdev->dev, "Failed to get gpio for cs\n");
			goto err_register;
		}

		hw->set_cs = s3c24xx_spi_gpiocs;
		gpio_direction_output(pdata->pin_cs, 1);
	} else
		hw->set_cs = pdata->set_cs;

	s3c24xx_spi_initialsetup(hw);

	/* register our spi controller */

	err = spi_bitbang_start(&hw->bitbang);
	if (err) {
		dev_err(&pdev->dev, "Failed to register SPI master\n");
		goto err_register;
	}

	return 0;

 err_register:
	clk_disable(hw->clk);

 err_no_pdata:
	spi_master_put(hw->master);
	return err;
}