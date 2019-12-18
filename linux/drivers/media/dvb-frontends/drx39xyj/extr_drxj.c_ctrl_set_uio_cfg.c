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
struct drxuio_cfg {int uio; int /*<<< orphan*/  mode; } ;
struct drxj_data {int /*<<< orphan*/  uio_irqn_mode; int /*<<< orphan*/  has_irqn; int /*<<< orphan*/  uio_gpio_mode; int /*<<< orphan*/  has_gpio; int /*<<< orphan*/  uio_sma_rx_mode; int /*<<< orphan*/  has_smarx; int /*<<< orphan*/  uio_sma_tx_mode; int /*<<< orphan*/  has_smatx; } ;
struct drx_demod_instance {int /*<<< orphan*/  my_i2c_dev_addr; scalar_t__ my_ext_attr; } ;

/* Variables and functions */
#define  DRX_UIO1 136 
#define  DRX_UIO2 135 
#define  DRX_UIO3 134 
#define  DRX_UIO4 133 
#define  DRX_UIO_MODE_DISABLE 132 
#define  DRX_UIO_MODE_FIRMWARE0 131 
#define  DRX_UIO_MODE_FIRMWARE_SAW 130 
#define  DRX_UIO_MODE_FIRMWARE_SMA 129 
#define  DRX_UIO_MODE_READWRITE 128 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SIO_PDR_GPIO_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_IRQN_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_SMA_RX_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_SMA_TX_CFG__A ; 
 int SIO_TOP_COMM_KEY_KEY ; 
 int /*<<< orphan*/  SIO_TOP_COMM_KEY__A ; 
 int drxj_dap_write_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int ctrl_set_uio_cfg(struct drx_demod_instance *demod, struct drxuio_cfg *uio_cfg)
{
	struct drxj_data *ext_attr = (struct drxj_data *) (NULL);
	int rc;

	if ((uio_cfg == NULL) || (demod == NULL))
		return -EINVAL;

	ext_attr = (struct drxj_data *) demod->my_ext_attr;

	/*  Write magic word to enable pdr reg write               */
	rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	switch (uio_cfg->uio) {
      /*====================================================================*/
	case DRX_UIO1:
		/* DRX_UIO1: SMA_TX UIO-1 */
		if (!ext_attr->has_smatx)
			return -EIO;
		switch (uio_cfg->mode) {
		case DRX_UIO_MODE_FIRMWARE_SMA:	/* fall through */
		case DRX_UIO_MODE_FIRMWARE_SAW:	/* fall through */
		case DRX_UIO_MODE_READWRITE:
			ext_attr->uio_sma_tx_mode = uio_cfg->mode;
			break;
		case DRX_UIO_MODE_DISABLE:
			ext_attr->uio_sma_tx_mode = uio_cfg->mode;
			/* pad configuration register is set 0 - input mode */
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_TX_CFG__A, 0, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		default:
			return -EINVAL;
		}		/* switch ( uio_cfg->mode ) */
		break;
      /*====================================================================*/
	case DRX_UIO2:
		/* DRX_UIO2: SMA_RX UIO-2 */
		if (!ext_attr->has_smarx)
			return -EIO;
		switch (uio_cfg->mode) {
		case DRX_UIO_MODE_FIRMWARE0:	/* fall through */
		case DRX_UIO_MODE_READWRITE:
			ext_attr->uio_sma_rx_mode = uio_cfg->mode;
			break;
		case DRX_UIO_MODE_DISABLE:
			ext_attr->uio_sma_rx_mode = uio_cfg->mode;
			/* pad configuration register is set 0 - input mode */
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_RX_CFG__A, 0, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		default:
			return -EINVAL;
			break;
		}		/* switch ( uio_cfg->mode ) */
		break;
      /*====================================================================*/
	case DRX_UIO3:
		/* DRX_UIO3: GPIO UIO-3 */
		if (!ext_attr->has_gpio)
			return -EIO;
		switch (uio_cfg->mode) {
		case DRX_UIO_MODE_FIRMWARE0:	/* fall through */
		case DRX_UIO_MODE_READWRITE:
			ext_attr->uio_gpio_mode = uio_cfg->mode;
			break;
		case DRX_UIO_MODE_DISABLE:
			ext_attr->uio_gpio_mode = uio_cfg->mode;
			/* pad configuration register is set 0 - input mode */
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_GPIO_CFG__A, 0, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		default:
			return -EINVAL;
			break;
		}		/* switch ( uio_cfg->mode ) */
		break;
      /*====================================================================*/
	case DRX_UIO4:
		/* DRX_UIO4: IRQN UIO-4 */
		if (!ext_attr->has_irqn)
			return -EIO;
		switch (uio_cfg->mode) {
		case DRX_UIO_MODE_READWRITE:
			ext_attr->uio_irqn_mode = uio_cfg->mode;
			break;
		case DRX_UIO_MODE_DISABLE:
			/* pad configuration register is set 0 - input mode */
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr, SIO_PDR_IRQN_CFG__A, 0, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			ext_attr->uio_irqn_mode = uio_cfg->mode;
			break;
		case DRX_UIO_MODE_FIRMWARE0:	/* fall through */
		default:
			return -EINVAL;
			break;
		}		/* switch ( uio_cfg->mode ) */
		break;
      /*====================================================================*/
	default:
		return -EINVAL;
	}			/* switch ( uio_cfg->uio ) */

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