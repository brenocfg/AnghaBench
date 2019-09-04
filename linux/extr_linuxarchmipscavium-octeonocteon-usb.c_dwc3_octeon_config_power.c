#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int output_sel; } ;
struct TYPE_6__ {int tx_oe; } ;
struct TYPE_5__ {int output_sel; } ;
union cvmx_gpio_bit_cfgx {void* u64; TYPE_3__ cn70xx; TYPE_2__ s; TYPE_1__ cn73xx; } ;
struct TYPE_8__ {int ppc_en; int ppc_active_high_en; } ;
union cvm_usbdrd_uctl_host_cfg {void* u64; TYPE_4__ s; } ;
typedef  int uint32_t ;
typedef  int u64 ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int CVMX_GPIO_BIT_CFGX (int) ; 
 int CVMX_GPIO_XBIT_CFGX (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OCTEON_CN73XX ; 
 int /*<<< orphan*/  OCTEON_CNF75XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 void* cvmx_read_csr (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int,void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/ * of_find_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_property_read_u32_array (struct device_node*,char*,int*,int) ; 

__attribute__((used)) static int dwc3_octeon_config_power(struct device *dev, u64 base)
{
#define UCTL_HOST_CFG	0xe0
	union cvm_usbdrd_uctl_host_cfg uctl_host_cfg;
	union cvmx_gpio_bit_cfgx gpio_bit;
	uint32_t gpio_pwr[3];
	int gpio, len, power_active_low;
	struct device_node *node = dev->of_node;
	int index = (base >> 24) & 1;

	if (of_find_property(node, "power", &len) != NULL) {
		if (len == 12) {
			of_property_read_u32_array(node, "power", gpio_pwr, 3);
			power_active_low = gpio_pwr[2] & 0x01;
			gpio = gpio_pwr[1];
		} else if (len == 8) {
			of_property_read_u32_array(node, "power", gpio_pwr, 2);
			power_active_low = 0;
			gpio = gpio_pwr[1];
		} else {
			dev_err(dev, "dwc3 controller clock init failure.\n");
			return -EINVAL;
		}
		if ((OCTEON_IS_MODEL(OCTEON_CN73XX) ||
		    OCTEON_IS_MODEL(OCTEON_CNF75XX))
		    && gpio <= 31) {
			gpio_bit.u64 = cvmx_read_csr(CVMX_GPIO_BIT_CFGX(gpio));
			gpio_bit.s.tx_oe = 1;
			gpio_bit.cn73xx.output_sel = (index == 0 ? 0x14 : 0x15);
			cvmx_write_csr(CVMX_GPIO_BIT_CFGX(gpio), gpio_bit.u64);
		} else if (gpio <= 15) {
			gpio_bit.u64 = cvmx_read_csr(CVMX_GPIO_BIT_CFGX(gpio));
			gpio_bit.s.tx_oe = 1;
			gpio_bit.cn70xx.output_sel = (index == 0 ? 0x14 : 0x19);
			cvmx_write_csr(CVMX_GPIO_BIT_CFGX(gpio), gpio_bit.u64);
		} else {
			gpio_bit.u64 = cvmx_read_csr(CVMX_GPIO_XBIT_CFGX(gpio));
			gpio_bit.s.tx_oe = 1;
			gpio_bit.cn70xx.output_sel = (index == 0 ? 0x14 : 0x19);
			cvmx_write_csr(CVMX_GPIO_XBIT_CFGX(gpio), gpio_bit.u64);
		}

		/* Enable XHCI power control and set if active high or low. */
		uctl_host_cfg.u64 = cvmx_read_csr(base + UCTL_HOST_CFG);
		uctl_host_cfg.s.ppc_en = 1;
		uctl_host_cfg.s.ppc_active_high_en = !power_active_low;
		cvmx_write_csr(base + UCTL_HOST_CFG, uctl_host_cfg.u64);
	} else {
		/* Disable XHCI power control and set if active high. */
		uctl_host_cfg.u64 = cvmx_read_csr(base + UCTL_HOST_CFG);
		uctl_host_cfg.s.ppc_en = 0;
		uctl_host_cfg.s.ppc_active_high_en = 0;
		cvmx_write_csr(base + UCTL_HOST_CFG, uctl_host_cfg.u64);
		dev_warn(dev, "dwc3 controller clock init failure.\n");
	}
	return 0;
}