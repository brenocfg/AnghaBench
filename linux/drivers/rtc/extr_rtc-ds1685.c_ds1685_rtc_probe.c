#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtc_device {int uie_unsupported; int nvram_old_abi; int /*<<< orphan*/  max_user_freq; int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; int /*<<< orphan*/ * ops; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct nvmem_config {char* name; struct ds1685_priv* priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; } ;
struct ds1685_rtc_platform_data {scalar_t__ regstep; int (* plat_read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;scalar_t__ no_irq; scalar_t__ uie_unsupported; scalar_t__ bcd_mode; scalar_t__ plat_post_ram_clear; scalar_t__ plat_wake_alarm; scalar_t__ plat_prepare_poweroff; scalar_t__ alloc_io_resources; int /*<<< orphan*/  (* plat_write ) (struct ds1685_priv*,int /*<<< orphan*/ ,int) ;} ;
struct ds1685_priv {int regstep; int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;int irq_num; scalar_t__ no_irq; struct rtc_device* dev; scalar_t__ uie_unsupported; int /*<<< orphan*/  (* write ) (struct ds1685_priv*,int /*<<< orphan*/ ,int) ;scalar_t__ bcd_mode; scalar_t__ post_ram_clear; scalar_t__ wake_alarm; scalar_t__ prepare_poweroff; scalar_t__ alloc_io_resources; int /*<<< orphan*/  regs; int /*<<< orphan*/  size; int /*<<< orphan*/  baseaddr; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  NVRAM_TOTAL_SZ ; 
 int PTR_ERR (struct rtc_device*) ; 
 int RTC_CTRL_4A_INCR ; 
 int RTC_CTRL_4A_RWK_MASK ; 
 int RTC_CTRL_4A_VRT2 ; 
 int RTC_CTRL_4B_E32K ; 
 int RTC_CTRL_4B_KSE ; 
 int RTC_CTRL_4B_RWK_MASK ; 
 int /*<<< orphan*/  RTC_CTRL_A ; 
 int RTC_CTRL_A_DV0 ; 
 int RTC_CTRL_A_DV1 ; 
 int RTC_CTRL_A_DV2 ; 
 int RTC_CTRL_A_RS_MASK ; 
 int /*<<< orphan*/  RTC_CTRL_B ; 
 int RTC_CTRL_B_2412 ; 
 int RTC_CTRL_B_DM ; 
 int RTC_CTRL_B_DSE ; 
 int RTC_CTRL_B_PAU_MASK ; 
 int RTC_CTRL_B_SET ; 
 int /*<<< orphan*/  RTC_CTRL_C ; 
 int /*<<< orphan*/  RTC_CTRL_D ; 
 int RTC_CTRL_D_VRT ; 
 int /*<<< orphan*/  RTC_EXT_CTRL_4A ; 
 int /*<<< orphan*/  RTC_EXT_CTRL_4B ; 
 int /*<<< orphan*/  RTC_HRS ; 
 int /*<<< orphan*/  RTC_HRS_12_BCD_MASK ; 
 int /*<<< orphan*/  RTC_HRS_12_BIN_MASK ; 
 int /*<<< orphan*/  RTC_HRS_24_BCD_MASK ; 
 int /*<<< orphan*/  RTC_HRS_24_BIN_MASK ; 
 int /*<<< orphan*/  RTC_HRS_ALARM ; 
 int RTC_HRS_AMPM_MASK ; 
 int /*<<< orphan*/  RTC_MAX_USER_FREQ ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_BEGIN_2000 ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_END_2099 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ds1685_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct platform_device*) ; 
 struct rtc_device* devm_rtc_allocate_device (TYPE_1__*) ; 
 int /*<<< orphan*/  ds1685_nvram_read ; 
 int /*<<< orphan*/  ds1685_nvram_write ; 
 int ds1685_read (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int ds1685_rtc_bcd2bin (struct ds1685_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ds1685_rtc_bin2bcd (struct ds1685_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1685_rtc_irq_handler ; 
 int /*<<< orphan*/  ds1685_rtc_ops ; 
 int /*<<< orphan*/  ds1685_rtc_switch_to_bank0 (struct ds1685_priv*) ; 
 int /*<<< orphan*/  ds1685_rtc_sysfs_misc_grp ; 
 int /*<<< orphan*/  ds1685_write (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ds1685_priv*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int rtc_add_group (struct rtc_device*,int /*<<< orphan*/ *) ; 
 int rtc_nvmem_register (struct rtc_device*,struct nvmem_config*) ; 
 int rtc_register_device (struct rtc_device*) ; 
 int stub1 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub12 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub15 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub16 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub17 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub18 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub20 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub21 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub23 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub24 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub25 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub26 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub27 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub4 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub6 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub7 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub8 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub9 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ds1685_rtc_probe(struct platform_device *pdev)
{
	struct rtc_device *rtc_dev;
	struct resource *res;
	struct ds1685_priv *rtc;
	struct ds1685_rtc_platform_data *pdata;
	u8 ctrla, ctrlb, hours;
	unsigned char am_pm;
	int ret = 0;
	struct nvmem_config nvmem_cfg = {
		.name = "ds1685_nvram",
		.size = NVRAM_TOTAL_SZ,
		.reg_read = ds1685_nvram_read,
		.reg_write = ds1685_nvram_write,
	};

	/* Get the platform data. */
	pdata = (struct ds1685_rtc_platform_data *) pdev->dev.platform_data;
	if (!pdata)
		return -ENODEV;

	/* Allocate memory for the rtc device. */
	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	/*
	 * Allocate/setup any IORESOURCE_MEM resources, if required.  Not all
	 * platforms put the RTC in an easy-access place.  Like the SGI Octane,
	 * which attaches the RTC to a "ByteBus", hooked to a SuperIO chip
	 * that sits behind the IOC3 PCI metadevice.
	 */
	if (pdata->alloc_io_resources) {
		/* Get the platform resources. */
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		if (!res)
			return -ENXIO;
		rtc->size = resource_size(res);

		/* Request a memory region. */
		/* XXX: mmio-only for now. */
		if (!devm_request_mem_region(&pdev->dev, res->start, rtc->size,
					     pdev->name))
			return -EBUSY;

		/*
		 * Set the base address for the rtc, and ioremap its
		 * registers.
		 */
		rtc->baseaddr = res->start;
		rtc->regs = devm_ioremap(&pdev->dev, res->start, rtc->size);
		if (!rtc->regs)
			return -ENOMEM;
	}
	rtc->alloc_io_resources = pdata->alloc_io_resources;

	/* Get the register step size. */
	if (pdata->regstep > 0)
		rtc->regstep = pdata->regstep;
	else
		rtc->regstep = 1;

	/* Platform read function, else default if mmio setup */
	if (pdata->plat_read)
		rtc->read = pdata->plat_read;
	else
		if (pdata->alloc_io_resources)
			rtc->read = ds1685_read;
		else
			return -ENXIO;

	/* Platform write function, else default if mmio setup */
	if (pdata->plat_write)
		rtc->write = pdata->plat_write;
	else
		if (pdata->alloc_io_resources)
			rtc->write = ds1685_write;
		else
			return -ENXIO;

	/* Platform pre-shutdown function, if defined. */
	if (pdata->plat_prepare_poweroff)
		rtc->prepare_poweroff = pdata->plat_prepare_poweroff;

	/* Platform wake_alarm function, if defined. */
	if (pdata->plat_wake_alarm)
		rtc->wake_alarm = pdata->plat_wake_alarm;

	/* Platform post_ram_clear function, if defined. */
	if (pdata->plat_post_ram_clear)
		rtc->post_ram_clear = pdata->plat_post_ram_clear;

	/* set the driver data. */
	platform_set_drvdata(pdev, rtc);

	/* Turn the oscillator on if is not already on (DV1 = 1). */
	ctrla = rtc->read(rtc, RTC_CTRL_A);
	if (!(ctrla & RTC_CTRL_A_DV1))
		ctrla |= RTC_CTRL_A_DV1;

	/* Enable the countdown chain (DV2 = 0) */
	ctrla &= ~(RTC_CTRL_A_DV2);

	/* Clear RS3-RS0 in Control A. */
	ctrla &= ~(RTC_CTRL_A_RS_MASK);

	/*
	 * All done with Control A.  Switch to Bank 1 for the remainder of
	 * the RTC setup so we have access to the extended functions.
	 */
	ctrla |= RTC_CTRL_A_DV0;
	rtc->write(rtc, RTC_CTRL_A, ctrla);

	/* Default to 32768kHz output. */
	rtc->write(rtc, RTC_EXT_CTRL_4B,
		   (rtc->read(rtc, RTC_EXT_CTRL_4B) | RTC_CTRL_4B_E32K));

	/* Set the SET bit in Control B so we can do some housekeeping. */
	rtc->write(rtc, RTC_CTRL_B,
		   (rtc->read(rtc, RTC_CTRL_B) | RTC_CTRL_B_SET));

	/* Read Ext Ctrl 4A and check the INCR bit to avoid a lockout. */
	while (rtc->read(rtc, RTC_EXT_CTRL_4A) & RTC_CTRL_4A_INCR)
		cpu_relax();

	/*
	 * If the platform supports BCD mode, then set DM=0 in Control B.
	 * Otherwise, set DM=1 for BIN mode.
	 */
	ctrlb = rtc->read(rtc, RTC_CTRL_B);
	if (pdata->bcd_mode)
		ctrlb &= ~(RTC_CTRL_B_DM);
	else
		ctrlb |= RTC_CTRL_B_DM;
	rtc->bcd_mode = pdata->bcd_mode;

	/*
	 * Disable Daylight Savings Time (DSE = 0).
	 * The RTC has hardcoded timezone information that is rendered
	 * obselete.  We'll let the OS deal with DST settings instead.
	 */
	if (ctrlb & RTC_CTRL_B_DSE)
		ctrlb &= ~(RTC_CTRL_B_DSE);

	/* Force 24-hour mode (2412 = 1). */
	if (!(ctrlb & RTC_CTRL_B_2412)) {
		/* Reinitialize the time hours. */
		hours = rtc->read(rtc, RTC_HRS);
		am_pm = hours & RTC_HRS_AMPM_MASK;
		hours = ds1685_rtc_bcd2bin(rtc, hours, RTC_HRS_12_BCD_MASK,
					   RTC_HRS_12_BIN_MASK);
		hours = ((hours == 12) ? 0 : ((am_pm) ? hours + 12 : hours));

		/* Enable 24-hour mode. */
		ctrlb |= RTC_CTRL_B_2412;

		/* Write back to Control B, including DM & DSE bits. */
		rtc->write(rtc, RTC_CTRL_B, ctrlb);

		/* Write the time hours back. */
		rtc->write(rtc, RTC_HRS,
			   ds1685_rtc_bin2bcd(rtc, hours,
					      RTC_HRS_24_BIN_MASK,
					      RTC_HRS_24_BCD_MASK));

		/* Reinitialize the alarm hours. */
		hours = rtc->read(rtc, RTC_HRS_ALARM);
		am_pm = hours & RTC_HRS_AMPM_MASK;
		hours = ds1685_rtc_bcd2bin(rtc, hours, RTC_HRS_12_BCD_MASK,
					   RTC_HRS_12_BIN_MASK);
		hours = ((hours == 12) ? 0 : ((am_pm) ? hours + 12 : hours));

		/* Write the alarm hours back. */
		rtc->write(rtc, RTC_HRS_ALARM,
			   ds1685_rtc_bin2bcd(rtc, hours,
					      RTC_HRS_24_BIN_MASK,
					      RTC_HRS_24_BCD_MASK));
	} else {
		/* 24-hour mode is already set, so write Control B back. */
		rtc->write(rtc, RTC_CTRL_B, ctrlb);
	}

	/* Unset the SET bit in Control B so the RTC can update. */
	rtc->write(rtc, RTC_CTRL_B,
		   (rtc->read(rtc, RTC_CTRL_B) & ~(RTC_CTRL_B_SET)));

	/* Check the main battery. */
	if (!(rtc->read(rtc, RTC_CTRL_D) & RTC_CTRL_D_VRT))
		dev_warn(&pdev->dev,
			 "Main battery is exhausted! RTC may be invalid!\n");

	/* Check the auxillary battery.  It is optional. */
	if (!(rtc->read(rtc, RTC_EXT_CTRL_4A) & RTC_CTRL_4A_VRT2))
		dev_warn(&pdev->dev,
			 "Aux battery is exhausted or not available.\n");

	/* Read Ctrl B and clear PIE/AIE/UIE. */
	rtc->write(rtc, RTC_CTRL_B,
		   (rtc->read(rtc, RTC_CTRL_B) & ~(RTC_CTRL_B_PAU_MASK)));

	/* Reading Ctrl C auto-clears PF/AF/UF. */
	rtc->read(rtc, RTC_CTRL_C);

	/* Read Ctrl 4B and clear RIE/WIE/KSE. */
	rtc->write(rtc, RTC_EXT_CTRL_4B,
		   (rtc->read(rtc, RTC_EXT_CTRL_4B) & ~(RTC_CTRL_4B_RWK_MASK)));

	/* Clear RF/WF/KF in Ctrl 4A. */
	rtc->write(rtc, RTC_EXT_CTRL_4A,
		   (rtc->read(rtc, RTC_EXT_CTRL_4A) & ~(RTC_CTRL_4A_RWK_MASK)));

	/*
	 * Re-enable KSE to handle power button events.  We do not enable
	 * WIE or RIE by default.
	 */
	rtc->write(rtc, RTC_EXT_CTRL_4B,
		   (rtc->read(rtc, RTC_EXT_CTRL_4B) | RTC_CTRL_4B_KSE));

	rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc_dev))
		return PTR_ERR(rtc_dev);

	rtc_dev->ops = &ds1685_rtc_ops;

	/* Century bit is useless because leap year fails in 1900 and 2100 */
	rtc_dev->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc_dev->range_max = RTC_TIMESTAMP_END_2099;

	/* Maximum periodic rate is 8192Hz (0.122070ms). */
	rtc_dev->max_user_freq = RTC_MAX_USER_FREQ;

	/* See if the platform doesn't support UIE. */
	if (pdata->uie_unsupported)
		rtc_dev->uie_unsupported = 1;
	rtc->uie_unsupported = pdata->uie_unsupported;

	rtc->dev = rtc_dev;

	/*
	 * Fetch the IRQ and setup the interrupt handler.
	 *
	 * Not all platforms have the IRQF pin tied to something.  If not, the
	 * RTC will still set the *IE / *F flags and raise IRQF in ctrlc, but
	 * there won't be an automatic way of notifying the kernel about it,
	 * unless ctrlc is explicitly polled.
	 */
	if (!pdata->no_irq) {
		ret = platform_get_irq(pdev, 0);
		if (ret <= 0)
			return ret;

		rtc->irq_num = ret;

		/* Request an IRQ. */
		ret = devm_request_threaded_irq(&pdev->dev, rtc->irq_num,
				       NULL, ds1685_rtc_irq_handler,
				       IRQF_SHARED | IRQF_ONESHOT,
				       pdev->name, pdev);

		/* Check to see if something came back. */
		if (unlikely(ret)) {
			dev_warn(&pdev->dev,
				 "RTC interrupt not available\n");
			rtc->irq_num = 0;
		}
	}
	rtc->no_irq = pdata->no_irq;

	/* Setup complete. */
	ds1685_rtc_switch_to_bank0(rtc);

	ret = rtc_add_group(rtc_dev, &ds1685_rtc_sysfs_misc_grp);
	if (ret)
		return ret;

	rtc_dev->nvram_old_abi = true;
	nvmem_cfg.priv = rtc;
	ret = rtc_nvmem_register(rtc_dev, &nvmem_cfg);
	if (ret)
		return ret;

	return rtc_register_device(rtc_dev);
}