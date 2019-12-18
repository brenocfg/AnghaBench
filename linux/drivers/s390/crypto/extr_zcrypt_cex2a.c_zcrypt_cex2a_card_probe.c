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
struct zcrypt_card {char* type_string; int online; int /*<<< orphan*/  user_space_type; int /*<<< orphan*/  speed_rating; void* max_exp_bit_length; void* max_mod_size; void* min_mod_size; struct ap_card* card; } ;
struct ap_device {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ device_type; } ;
struct ap_card {struct zcrypt_card* private; int /*<<< orphan*/  functions; TYPE_1__ ap_dev; } ;
typedef  int /*<<< orphan*/  CEX3A_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX2A_SPEED_IDX ;

/* Variables and functions */
 scalar_t__ AP_DEVICE_TYPE_CEX2A ; 
 scalar_t__ AP_DEVICE_TYPE_CEX3A ; 
 int /*<<< orphan*/  AP_FUNC_CRT4K ; 
 int /*<<< orphan*/  AP_FUNC_MEX4K ; 
 void* CEX2A_MAX_MOD_SIZE ; 
 void* CEX2A_MIN_MOD_SIZE ; 
 void* CEX3A_MAX_MOD_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ZCRYPT_CEX2A ; 
 int /*<<< orphan*/  ZCRYPT_CEX3A ; 
 scalar_t__ ap_test_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 struct ap_card* to_ap_card (int /*<<< orphan*/ *) ; 
 struct zcrypt_card* zcrypt_card_alloc () ; 
 int /*<<< orphan*/  zcrypt_card_free (struct zcrypt_card*) ; 
 int zcrypt_card_register (struct zcrypt_card*) ; 

__attribute__((used)) static int zcrypt_cex2a_card_probe(struct ap_device *ap_dev)
{
	/*
	 * Normalized speed ratings per crypto adapter
	 * MEX_1k, MEX_2k, MEX_4k, CRT_1k, CRT_2k, CRT_4k, RNG, SECKEY
	 */
	static const int CEX2A_SPEED_IDX[] = {
		800, 1000, 2000,  900, 1200, 2400, 0, 0};
	static const int CEX3A_SPEED_IDX[] = {
		400,  500, 1000,  450,	550, 1200, 0, 0};

	struct ap_card *ac = to_ap_card(&ap_dev->device);
	struct zcrypt_card *zc;
	int rc = 0;

	zc = zcrypt_card_alloc();
	if (!zc)
		return -ENOMEM;
	zc->card = ac;
	ac->private = zc;

	if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX2A) {
		zc->min_mod_size = CEX2A_MIN_MOD_SIZE;
		zc->max_mod_size = CEX2A_MAX_MOD_SIZE;
		memcpy(zc->speed_rating, CEX2A_SPEED_IDX,
		       sizeof(CEX2A_SPEED_IDX));
		zc->max_exp_bit_length = CEX2A_MAX_MOD_SIZE;
		zc->type_string = "CEX2A";
		zc->user_space_type = ZCRYPT_CEX2A;
	} else if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX3A) {
		zc->min_mod_size = CEX2A_MIN_MOD_SIZE;
		zc->max_mod_size = CEX2A_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX2A_MAX_MOD_SIZE;
		if (ap_test_bit(&ac->functions, AP_FUNC_MEX4K) &&
		    ap_test_bit(&ac->functions, AP_FUNC_CRT4K)) {
			zc->max_mod_size = CEX3A_MAX_MOD_SIZE;
			zc->max_exp_bit_length = CEX3A_MAX_MOD_SIZE;
		}
		memcpy(zc->speed_rating, CEX3A_SPEED_IDX,
		       sizeof(CEX3A_SPEED_IDX));
		zc->type_string = "CEX3A";
		zc->user_space_type = ZCRYPT_CEX3A;
	} else {
		zcrypt_card_free(zc);
		return -ENODEV;
	}
	zc->online = 1;

	rc = zcrypt_card_register(zc);
	if (rc) {
		ac->private = NULL;
		zcrypt_card_free(zc);
	}

	return rc;
}