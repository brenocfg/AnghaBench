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
typedef  int u16 ;
struct drxuio_data {int uio; int value; } ;
struct drxj_data {int /*<<< orphan*/  uio_irqn_mode; int /*<<< orphan*/  has_irqn; int /*<<< orphan*/  uio_gpio_mode; int /*<<< orphan*/  has_gpio; int /*<<< orphan*/  uio_sma_rx_mode; int /*<<< orphan*/  has_smarx; int /*<<< orphan*/  uio_sma_tx_mode; int /*<<< orphan*/  has_smatx; } ;
struct drx_demod_instance {int /*<<< orphan*/  my_i2c_dev_addr; scalar_t__ my_ext_attr; } ;

/* Variables and functions */
#define  DRX_UIO1 131 
#define  DRX_UIO2 130 
#define  DRX_UIO3 129 
#define  DRX_UIO4 128 
 int /*<<< orphan*/  DRX_UIO_MODE_FIRMWARE_SAW ; 
 int /*<<< orphan*/  DRX_UIO_MODE_READWRITE ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SIO_PDR_GPIO_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_IRQN_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_SMA_RX_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_SMA_TX_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_UIO_OUT_HI__A ; 
 int /*<<< orphan*/  SIO_PDR_UIO_OUT_LO__A ; 
 int SIO_TOP_COMM_KEY_KEY ; 
 int /*<<< orphan*/  SIO_TOP_COMM_KEY__A ; 
 int drxj_dap_read_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int
ctrl_uio_write(struct drx_demod_instance *demod, struct drxuio_data *uio_data)
{
	struct drxj_data *ext_attr = (struct drxj_data *) (NULL);
	int rc;
	u16 pin_cfg_value = 0;
	u16 value = 0;

	if ((uio_data == NULL) || (demod == NULL))
		return -EINVAL;

	ext_attr = (struct drxj_data *) demod->my_ext_attr;

	/*  Write magic word to enable pdr reg write               */
	rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	switch (uio_data->uio) {
      /*====================================================================*/
	case DRX_UIO1:
		/* DRX_UIO1: SMA_TX UIO-1 */
		if (!ext_attr->has_smatx)
			return -EIO;
		if ((ext_attr->uio_sma_tx_mode != DRX_UIO_MODE_READWRITE)
		    && (ext_attr->uio_sma_tx_mode != DRX_UIO_MODE_FIRMWARE_SAW)) {
			return -EIO;
		}
		pin_cfg_value = 0;
		/* io_pad_cfg register (8 bit reg.) MSB bit is 1 (default value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to power 2 (23 mA) */

		/* write to io pad configuration register - output mode */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_TX_CFG__A, pin_cfg_value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, &value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		if (!uio_data->value)
			value &= 0x7FFF;	/* write zero to 15th bit - 1st UIO */
		else
			value |= 0x8000;	/* write one to 15th bit - 1st UIO */

		/* write back to io data output register */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
   /*======================================================================*/
	case DRX_UIO2:
		/* DRX_UIO2: SMA_RX UIO-2 */
		if (!ext_attr->has_smarx)
			return -EIO;
		if (ext_attr->uio_sma_rx_mode != DRX_UIO_MODE_READWRITE)
			return -EIO;

		pin_cfg_value = 0;
		/* io_pad_cfg register (8 bit reg.) MSB bit is 1 (default value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to power 2 (23 mA) */

		/* write to io pad configuration register - output mode */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_RX_CFG__A, pin_cfg_value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, &value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		if (!uio_data->value)
			value &= 0xBFFF;	/* write zero to 14th bit - 2nd UIO */
		else
			value |= 0x4000;	/* write one to 14th bit - 2nd UIO */

		/* write back to io data output register */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
   /*====================================================================*/
	case DRX_UIO3:
		/* DRX_UIO3: ASEL UIO-3 */
		if (!ext_attr->has_gpio)
			return -EIO;
		if (ext_attr->uio_gpio_mode != DRX_UIO_MODE_READWRITE)
			return -EIO;

		pin_cfg_value = 0;
		/* io_pad_cfg register (8 bit reg.) MSB bit is 1 (default value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to power 2 (23 mA) */

		/* write to io pad configuration register - output mode */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_GPIO_CFG__A, pin_cfg_value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_HI__A, &value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		if (!uio_data->value)
			value &= 0xFFFB;	/* write zero to 2nd bit - 3rd UIO */
		else
			value |= 0x0004;	/* write one to 2nd bit - 3rd UIO */

		/* write back to io data output register */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_HI__A, value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
   /*=====================================================================*/
	case DRX_UIO4:
		/* DRX_UIO4: IRQN UIO-4 */
		if (!ext_attr->has_irqn)
			return -EIO;

		if (ext_attr->uio_irqn_mode != DRX_UIO_MODE_READWRITE)
			return -EIO;

		pin_cfg_value = 0;
		/* io_pad_cfg register (8 bit reg.) MSB bit is 1 (default value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to power 2 (23 mA) */

		/* write to io pad configuration register - output mode */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_IRQN_CFG__A, pin_cfg_value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, &value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		if (uio_data->value == false)
			value &= 0xEFFF;	/* write zero to 12th bit - 4th UIO */
		else
			value |= 0x1000;	/* write one to 12th bit - 4th UIO */

		/* write back to io data output register */
		rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, value, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
      /*=====================================================================*/
	default:
		return -EINVAL;
	}			/* switch ( uio_data->uio ) */

	/*  Write magic word to disable pdr reg write               */
	rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	return 0;
rw_error:
	return rc;
}