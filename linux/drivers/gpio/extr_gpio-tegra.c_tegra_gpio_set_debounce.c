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
struct tegra_gpio_info {struct tegra_gpio_bank* bank_info; } ;
struct tegra_gpio_bank {unsigned int* dbc_cnt; int /*<<< orphan*/ * dbc_lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 size_t GPIO_BANK (unsigned int) ; 
 int /*<<< orphan*/  GPIO_DBC_CNT (struct tegra_gpio_info*,unsigned int) ; 
 int /*<<< orphan*/  GPIO_MSK_DBC_EN (struct tegra_gpio_info*,unsigned int) ; 
 unsigned int GPIO_PORT (unsigned int) ; 
 struct tegra_gpio_info* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_gpio_mask_write (struct tegra_gpio_info*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  tegra_gpio_writel (struct tegra_gpio_info*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_gpio_set_debounce(struct gpio_chip *chip, unsigned int offset,
				   unsigned int debounce)
{
	struct tegra_gpio_info *tgi = gpiochip_get_data(chip);
	struct tegra_gpio_bank *bank = &tgi->bank_info[GPIO_BANK(offset)];
	unsigned int debounce_ms = DIV_ROUND_UP(debounce, 1000);
	unsigned long flags;
	unsigned int port;

	if (!debounce_ms) {
		tegra_gpio_mask_write(tgi, GPIO_MSK_DBC_EN(tgi, offset),
				      offset, 0);
		return 0;
	}

	debounce_ms = min(debounce_ms, 255U);
	port = GPIO_PORT(offset);

	/* There is only one debounce count register per port and hence
	 * set the maximum of current and requested debounce time.
	 */
	spin_lock_irqsave(&bank->dbc_lock[port], flags);
	if (bank->dbc_cnt[port] < debounce_ms) {
		tegra_gpio_writel(tgi, debounce_ms, GPIO_DBC_CNT(tgi, offset));
		bank->dbc_cnt[port] = debounce_ms;
	}
	spin_unlock_irqrestore(&bank->dbc_lock[port], flags);

	tegra_gpio_mask_write(tgi, GPIO_MSK_DBC_EN(tgi, offset), offset, 1);

	return 0;
}