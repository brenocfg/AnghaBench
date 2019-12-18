#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct iwl_trans {int /*<<< orphan*/  dev; TYPE_2__* trans_cfg; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int eeprom_size; int /*<<< orphan*/  shadow_ram_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_EEPROM_GP ; 
 int CSR_EEPROM_GP_IF_OWNER_MSK ; 
 int /*<<< orphan*/  CSR_EEPROM_REG ; 
 int CSR_EEPROM_REG_MSK_ADDR ; 
 int /*<<< orphan*/  CSR_EEPROM_REG_READ_VALID_MSK ; 
 int /*<<< orphan*/  CSR_OTP_GP_REG ; 
 int CSR_OTP_GP_REG_ECC_CORR_STATUS_MSK ; 
 int CSR_OTP_GP_REG_ECC_UNCORR_STATUS_MSK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DEBUG_EEPROM (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  IWL_EEPROM_ACCESS_TIMEOUT ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,...) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int iwl_eeprom_acquire_semaphore (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_eeprom_release_semaphore (struct iwl_trans*) ; 
 int iwl_eeprom_verify_signature (struct iwl_trans*,int) ; 
 int iwl_find_otp_image (struct iwl_trans*,int*) ; 
 int iwl_init_otp_access (struct iwl_trans*) ; 
 int iwl_nvm_is_otp (struct iwl_trans*) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_read_otp_word (struct iwl_trans*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

int iwl_read_eeprom(struct iwl_trans *trans, u8 **eeprom, size_t *eeprom_size)
{
	__le16 *e;
	u32 gp = iwl_read32(trans, CSR_EEPROM_GP);
	int sz;
	int ret;
	u16 addr;
	u16 validblockaddr = 0;
	u16 cache_addr = 0;
	int nvm_is_otp;

	if (!eeprom || !eeprom_size)
		return -EINVAL;

	nvm_is_otp = iwl_nvm_is_otp(trans);
	if (nvm_is_otp < 0)
		return nvm_is_otp;

	sz = trans->trans_cfg->base_params->eeprom_size;
	IWL_DEBUG_EEPROM(trans->dev, "NVM size = %d\n", sz);

	e = kmalloc(sz, GFP_KERNEL);
	if (!e)
		return -ENOMEM;

	ret = iwl_eeprom_verify_signature(trans, nvm_is_otp);
	if (ret < 0) {
		IWL_ERR(trans, "EEPROM not found, EEPROM_GP=0x%08x\n", gp);
		goto err_free;
	}

	/* Make sure driver (instead of uCode) is allowed to read EEPROM */
	ret = iwl_eeprom_acquire_semaphore(trans);
	if (ret < 0) {
		IWL_ERR(trans, "Failed to acquire EEPROM semaphore.\n");
		goto err_free;
	}

	if (nvm_is_otp) {
		ret = iwl_init_otp_access(trans);
		if (ret) {
			IWL_ERR(trans, "Failed to initialize OTP access.\n");
			goto err_unlock;
		}

		iwl_write32(trans, CSR_EEPROM_GP,
			    iwl_read32(trans, CSR_EEPROM_GP) &
			    ~CSR_EEPROM_GP_IF_OWNER_MSK);

		iwl_set_bit(trans, CSR_OTP_GP_REG,
			    CSR_OTP_GP_REG_ECC_CORR_STATUS_MSK |
			    CSR_OTP_GP_REG_ECC_UNCORR_STATUS_MSK);
		/* traversing the linked list if no shadow ram supported */
		if (!trans->trans_cfg->base_params->shadow_ram_support) {
			ret = iwl_find_otp_image(trans, &validblockaddr);
			if (ret)
				goto err_unlock;
		}
		for (addr = validblockaddr; addr < validblockaddr + sz;
		     addr += sizeof(u16)) {
			__le16 eeprom_data;

			ret = iwl_read_otp_word(trans, addr, &eeprom_data);
			if (ret)
				goto err_unlock;
			e[cache_addr / 2] = eeprom_data;
			cache_addr += sizeof(u16);
		}
	} else {
		/* eeprom is an array of 16bit values */
		for (addr = 0; addr < sz; addr += sizeof(u16)) {
			u32 r;

			iwl_write32(trans, CSR_EEPROM_REG,
				    CSR_EEPROM_REG_MSK_ADDR & (addr << 1));

			ret = iwl_poll_bit(trans, CSR_EEPROM_REG,
					   CSR_EEPROM_REG_READ_VALID_MSK,
					   CSR_EEPROM_REG_READ_VALID_MSK,
					   IWL_EEPROM_ACCESS_TIMEOUT);
			if (ret < 0) {
				IWL_ERR(trans,
					"Time out reading EEPROM[%d]\n", addr);
				goto err_unlock;
			}
			r = iwl_read32(trans, CSR_EEPROM_REG);
			e[addr / 2] = cpu_to_le16(r >> 16);
		}
	}

	IWL_DEBUG_EEPROM(trans->dev, "NVM Type: %s\n",
			 nvm_is_otp ? "OTP" : "EEPROM");

	iwl_eeprom_release_semaphore(trans);

	*eeprom_size = sz;
	*eeprom = (u8 *)e;
	return 0;

 err_unlock:
	iwl_eeprom_release_semaphore(trans);
 err_free:
	kfree(e);

	return ret;
}