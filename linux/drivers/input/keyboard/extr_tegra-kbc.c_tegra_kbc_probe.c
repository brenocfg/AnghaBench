#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tegra_kbc {int max_keys; int num_rows_and_columns; scalar_t__ irq; int /*<<< orphan*/  wakeup; TYPE_4__* idev; int /*<<< orphan*/  keycode; TYPE_3__* hw_support; scalar_t__ keymap_data; scalar_t__ use_fn_map; scalar_t__ repoll_dly; scalar_t__ repeat_cnt; int /*<<< orphan*/  debounce_cnt; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; int /*<<< orphan*/  mmio; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct of_device_id {TYPE_3__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_12__ {int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int max_rows; int max_columns; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBC_CYCLE_MS ; 
 int /*<<< orphan*/  KBC_MAX_DEBOUNCE_CNT ; 
 scalar_t__ KBC_ROW_SCAN_DLY ; 
 unsigned int KBC_ROW_SCAN_TIME ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra_kbc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_kbc*) ; 
 int /*<<< orphan*/  devm_reset_control_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int input_register_device (TYPE_4__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_4__*,struct tegra_kbc*) ; 
 int matrix_keypad_build_keymap (scalar_t__,int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_kbc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_kbc_check_pin_cfg (struct tegra_kbc*,int*) ; 
 int /*<<< orphan*/  tegra_kbc_close ; 
 int /*<<< orphan*/  tegra_kbc_isr ; 
 int /*<<< orphan*/  tegra_kbc_keypress_timer ; 
 int /*<<< orphan*/  tegra_kbc_of_match ; 
 int /*<<< orphan*/  tegra_kbc_open ; 
 int tegra_kbc_parse_dt (struct tegra_kbc*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_kbc_probe(struct platform_device *pdev)
{
	struct tegra_kbc *kbc;
	struct resource *res;
	int err;
	int num_rows = 0;
	unsigned int debounce_cnt;
	unsigned int scan_time_rows;
	unsigned int keymap_rows;
	const struct of_device_id *match;

	match = of_match_device(tegra_kbc_of_match, &pdev->dev);

	kbc = devm_kzalloc(&pdev->dev, sizeof(*kbc), GFP_KERNEL);
	if (!kbc) {
		dev_err(&pdev->dev, "failed to alloc memory for kbc\n");
		return -ENOMEM;
	}

	kbc->dev = &pdev->dev;
	kbc->hw_support = match->data;
	kbc->max_keys = kbc->hw_support->max_rows *
				kbc->hw_support->max_columns;
	kbc->num_rows_and_columns = kbc->hw_support->max_rows +
					kbc->hw_support->max_columns;
	keymap_rows = kbc->max_keys;
	spin_lock_init(&kbc->lock);

	err = tegra_kbc_parse_dt(kbc);
	if (err)
		return err;

	if (!tegra_kbc_check_pin_cfg(kbc, &num_rows))
		return -EINVAL;

	kbc->irq = platform_get_irq(pdev, 0);
	if (kbc->irq < 0)
		return -ENXIO;

	kbc->idev = devm_input_allocate_device(&pdev->dev);
	if (!kbc->idev) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	timer_setup(&kbc->timer, tegra_kbc_keypress_timer, 0);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	kbc->mmio = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(kbc->mmio))
		return PTR_ERR(kbc->mmio);

	kbc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(kbc->clk)) {
		dev_err(&pdev->dev, "failed to get keyboard clock\n");
		return PTR_ERR(kbc->clk);
	}

	kbc->rst = devm_reset_control_get(&pdev->dev, "kbc");
	if (IS_ERR(kbc->rst)) {
		dev_err(&pdev->dev, "failed to get keyboard reset\n");
		return PTR_ERR(kbc->rst);
	}

	/*
	 * The time delay between two consecutive reads of the FIFO is
	 * the sum of the repeat time and the time taken for scanning
	 * the rows. There is an additional delay before the row scanning
	 * starts. The repoll delay is computed in milliseconds.
	 */
	debounce_cnt = min(kbc->debounce_cnt, KBC_MAX_DEBOUNCE_CNT);
	scan_time_rows = (KBC_ROW_SCAN_TIME + debounce_cnt) * num_rows;
	kbc->repoll_dly = KBC_ROW_SCAN_DLY + scan_time_rows + kbc->repeat_cnt;
	kbc->repoll_dly = DIV_ROUND_UP(kbc->repoll_dly, KBC_CYCLE_MS);

	kbc->idev->name = pdev->name;
	kbc->idev->id.bustype = BUS_HOST;
	kbc->idev->dev.parent = &pdev->dev;
	kbc->idev->open = tegra_kbc_open;
	kbc->idev->close = tegra_kbc_close;

	if (kbc->keymap_data && kbc->use_fn_map)
		keymap_rows *= 2;

	err = matrix_keypad_build_keymap(kbc->keymap_data, NULL,
					 keymap_rows,
					 kbc->hw_support->max_columns,
					 kbc->keycode, kbc->idev);
	if (err) {
		dev_err(&pdev->dev, "failed to setup keymap\n");
		return err;
	}

	__set_bit(EV_REP, kbc->idev->evbit);
	input_set_capability(kbc->idev, EV_MSC, MSC_SCAN);

	input_set_drvdata(kbc->idev, kbc);

	err = devm_request_irq(&pdev->dev, kbc->irq, tegra_kbc_isr,
			       IRQF_TRIGGER_HIGH, pdev->name, kbc);
	if (err) {
		dev_err(&pdev->dev, "failed to request keyboard IRQ\n");
		return err;
	}

	disable_irq(kbc->irq);

	err = input_register_device(kbc->idev);
	if (err) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return err;
	}

	platform_set_drvdata(pdev, kbc);
	device_init_wakeup(&pdev->dev, kbc->wakeup);

	return 0;
}