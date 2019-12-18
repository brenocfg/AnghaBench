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
struct zcrypt_card {char* type_string; int online; void* max_exp_bit_length; void* max_mod_size; int /*<<< orphan*/  min_mod_size; int /*<<< orphan*/  speed_rating; int /*<<< orphan*/  user_space_type; struct ap_card* card; } ;
struct ap_device {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int device_type; } ;
struct ap_card {struct zcrypt_card* private; TYPE_1__ ap_dev; } ;
typedef  int /*<<< orphan*/  CEX3C_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX2C_SPEED_IDX ;

/* Variables and functions */
#define  AP_DEVICE_TYPE_CEX2C 129 
#define  AP_DEVICE_TYPE_CEX3C 128 
 void* CEX2C_MAX_MOD_SIZE ; 
 int /*<<< orphan*/  CEX2C_MIN_MOD_SIZE ; 
 void* CEX3C_MAX_MOD_SIZE ; 
 int /*<<< orphan*/  CEX3C_MIN_MOD_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ZCRYPT_CEX2C ; 
 int /*<<< orphan*/  ZCRYPT_CEX3C ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 struct ap_card* to_ap_card (int /*<<< orphan*/ *) ; 
 struct zcrypt_card* zcrypt_card_alloc () ; 
 int /*<<< orphan*/  zcrypt_card_free (struct zcrypt_card*) ; 
 int zcrypt_card_register (struct zcrypt_card*) ; 

__attribute__((used)) static int zcrypt_cex2c_card_probe(struct ap_device *ap_dev)
{
	/*
	 * Normalized speed ratings per crypto adapter
	 * MEX_1k, MEX_2k, MEX_4k, CRT_1k, CRT_2k, CRT_4k, RNG, SECKEY
	 */
	static const int CEX2C_SPEED_IDX[] = {
		1000, 1400, 2400, 1100, 1500, 2600, 100, 12};
	static const int CEX3C_SPEED_IDX[] = {
		500,  700, 1400,  550,	800, 1500,  80, 10};

	struct ap_card *ac = to_ap_card(&ap_dev->device);
	struct zcrypt_card *zc;
	int rc = 0;

	zc = zcrypt_card_alloc();
	if (!zc)
		return -ENOMEM;
	zc->card = ac;
	ac->private = zc;
	switch (ac->ap_dev.device_type) {
	case AP_DEVICE_TYPE_CEX2C:
		zc->user_space_type = ZCRYPT_CEX2C;
		zc->type_string = "CEX2C";
		memcpy(zc->speed_rating, CEX2C_SPEED_IDX,
		       sizeof(CEX2C_SPEED_IDX));
		zc->min_mod_size = CEX2C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX2C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX2C_MAX_MOD_SIZE;
		break;
	case AP_DEVICE_TYPE_CEX3C:
		zc->user_space_type = ZCRYPT_CEX3C;
		zc->type_string = "CEX3C";
		memcpy(zc->speed_rating, CEX3C_SPEED_IDX,
		       sizeof(CEX3C_SPEED_IDX));
		zc->min_mod_size = CEX3C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX3C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX3C_MAX_MOD_SIZE;
		break;
	default:
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