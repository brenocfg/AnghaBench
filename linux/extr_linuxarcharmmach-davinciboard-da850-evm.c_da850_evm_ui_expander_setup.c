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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 size_t DA850_EVM_UI_EXP_SEL_A ; 
 size_t DA850_EVM_UI_EXP_SEL_B ; 
 size_t DA850_EVM_UI_EXP_SEL_C ; 
 int /*<<< orphan*/  da850_evm_setup_emac_rmii (int) ; 
 int /*<<< orphan*/  da850_evm_setup_nor_nand () ; 
 int /*<<< orphan*/  da850_evm_setup_video_port (int) ; 
 int /*<<< orphan*/ * da850_evm_ui_exp ; 
 int /*<<< orphan*/  da850_evm_ui_keys_device ; 
 int /*<<< orphan*/  da850_evm_ui_keys_init (unsigned int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 int platform_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static int da850_evm_ui_expander_setup(struct i2c_client *client, unsigned gpio,
						unsigned ngpio, void *c)
{
	int sel_a, sel_b, sel_c, ret;

	sel_a = gpio + DA850_EVM_UI_EXP_SEL_A;
	sel_b = gpio + DA850_EVM_UI_EXP_SEL_B;
	sel_c = gpio + DA850_EVM_UI_EXP_SEL_C;

	ret = gpio_request(sel_a, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_A]);
	if (ret) {
		pr_warn("Cannot open UI expander pin %d\n", sel_a);
		goto exp_setup_sela_fail;
	}

	ret = gpio_request(sel_b, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_B]);
	if (ret) {
		pr_warn("Cannot open UI expander pin %d\n", sel_b);
		goto exp_setup_selb_fail;
	}

	ret = gpio_request(sel_c, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_C]);
	if (ret) {
		pr_warn("Cannot open UI expander pin %d\n", sel_c);
		goto exp_setup_selc_fail;
	}

	/* deselect all functionalities */
	gpio_direction_output(sel_a, 1);
	gpio_direction_output(sel_b, 1);
	gpio_direction_output(sel_c, 1);

	da850_evm_ui_keys_init(gpio);
	ret = platform_device_register(&da850_evm_ui_keys_device);
	if (ret) {
		pr_warn("Could not register UI GPIO expander push-buttons");
		goto exp_setup_keys_fail;
	}

	pr_info("DA850/OMAP-L138 EVM UI card detected\n");

	da850_evm_setup_nor_nand();

	da850_evm_setup_emac_rmii(sel_a);

	da850_evm_setup_video_port(sel_c);

	return 0;

exp_setup_keys_fail:
	gpio_free(sel_c);
exp_setup_selc_fail:
	gpio_free(sel_b);
exp_setup_selb_fail:
	gpio_free(sel_a);
exp_setup_sela_fail:
	return ret;
}