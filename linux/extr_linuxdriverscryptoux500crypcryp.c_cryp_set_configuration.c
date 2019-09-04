#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cryp_device_data {TYPE_1__* base; } ;
struct cryp_config {int keysize; int algodir; int algomode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr; } ;

/* Variables and functions */
 int CRYP_ALGORITHM_DECRYPT ; 
 int CRYP_ALGORITHM_ENCRYPT ; 
 int CRYP_ALGO_AES_CBC ; 
 int CRYP_ALGO_AES_ECB ; 
 int CRYP_CRYPEN_ENABLE ; 
 int CRYP_CR_ALGODIR_POS ; 
 int CRYP_CR_ALGOMODE_POS ; 
 int CRYP_CR_CRYPEN_POS ; 
 int CRYP_CR_KEYSIZE_POS ; 
 int CRYP_CR_KSE_POS ; 
 int EINVAL ; 
 int KSE_ENABLED ; 
 int /*<<< orphan*/  cryp_wait_until_done (struct cryp_device_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ *) ; 

int cryp_set_configuration(struct cryp_device_data *device_data,
			   struct cryp_config *cryp_config,
			   u32 *control_register)
{
	u32 cr_for_kse;

	if (NULL == device_data || NULL == cryp_config)
		return -EINVAL;

	*control_register |= (cryp_config->keysize << CRYP_CR_KEYSIZE_POS);

	/* Prepare key for decryption in AES_ECB and AES_CBC mode. */
	if ((CRYP_ALGORITHM_DECRYPT == cryp_config->algodir) &&
	    ((CRYP_ALGO_AES_ECB == cryp_config->algomode) ||
	     (CRYP_ALGO_AES_CBC == cryp_config->algomode))) {
		cr_for_kse = *control_register;
		/*
		 * This seems a bit odd, but it is indeed needed to set this to
		 * encrypt even though it is a decryption that we are doing. It
		 * also mentioned in the design spec that you need to do this.
		 * After the keyprepartion for decrypting is done you should set
		 * algodir back to decryption, which is done outside this if
		 * statement.
		 *
		 * According to design specification we should set mode ECB
		 * during key preparation even though we might be running CBC
		 * when enter this function.
		 *
		 * Writing to KSE_ENABLED will drop CRYPEN when key preparation
		 * is done. Therefore we need to set CRYPEN again outside this
		 * if statement when running decryption.
		 */
		cr_for_kse |= ((CRYP_ALGORITHM_ENCRYPT << CRYP_CR_ALGODIR_POS) |
			       (CRYP_ALGO_AES_ECB << CRYP_CR_ALGOMODE_POS) |
			       (CRYP_CRYPEN_ENABLE << CRYP_CR_CRYPEN_POS) |
			       (KSE_ENABLED << CRYP_CR_KSE_POS));

		writel_relaxed(cr_for_kse, &device_data->base->cr);
		cryp_wait_until_done(device_data);
	}

	*control_register |=
		((cryp_config->algomode << CRYP_CR_ALGOMODE_POS) |
		 (cryp_config->algodir << CRYP_CR_ALGODIR_POS));

	return 0;
}