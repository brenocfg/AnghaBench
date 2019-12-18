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
typedef  scalar_t__ u16 ;
struct pmbus_driver_info {int dummy; } ;
struct lm25066_data {int /*<<< orphan*/  rlimit; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST (int,int) ; 
 int ENODATA ; 
 int LM25056_VAUX_OV_WARN_LIMIT ; 
 int LM25056_VAUX_UV_WARN_LIMIT ; 
 int /*<<< orphan*/  LM25066_CLEAR_PIN_PEAK ; 
 int LM25066_MFR_IIN_OC_WARN_LIMIT ; 
 int LM25066_MFR_PIN_OP_WARN_LIMIT ; 
 int /*<<< orphan*/  LM25066_SAMPLES_FOR_AVG ; 
 int /*<<< orphan*/  LM25066_SAMPLES_FOR_AVG_MAX ; 
#define  PMBUS_IIN_OC_FAULT_LIMIT 143 
#define  PMBUS_IIN_OC_WARN_LIMIT 142 
#define  PMBUS_OT_FAULT_LIMIT 141 
#define  PMBUS_OT_WARN_LIMIT 140 
#define  PMBUS_PIN_OP_WARN_LIMIT 139 
#define  PMBUS_POUT_OP_FAULT_LIMIT 138 
#define  PMBUS_POUT_OP_WARN_LIMIT 137 
#define  PMBUS_VIN_OV_FAULT_LIMIT 136 
#define  PMBUS_VIN_OV_WARN_LIMIT 135 
#define  PMBUS_VIN_UV_FAULT_LIMIT 134 
#define  PMBUS_VIN_UV_WARN_LIMIT 133 
#define  PMBUS_VIRT_RESET_PIN_HISTORY 132 
#define  PMBUS_VIRT_SAMPLES 131 
#define  PMBUS_VIRT_VMON_OV_WARN_LIMIT 130 
#define  PMBUS_VIRT_VMON_UV_WARN_LIMIT 129 
#define  PMBUS_VOUT_UV_WARN_LIMIT 128 
 scalar_t__ clamp_val (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (scalar_t__) ; 
 int /*<<< orphan*/  pmbus_clear_cache (struct i2c_client*) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 int pmbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct lm25066_data* to_lm25066_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int lm25066_write_word_data(struct i2c_client *client, int page, int reg,
				   u16 word)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	const struct lm25066_data *data = to_lm25066_data(info);
	int ret;

	switch (reg) {
	case PMBUS_POUT_OP_FAULT_LIMIT:
	case PMBUS_POUT_OP_WARN_LIMIT:
	case PMBUS_VOUT_UV_WARN_LIMIT:
	case PMBUS_OT_FAULT_LIMIT:
	case PMBUS_OT_WARN_LIMIT:
	case PMBUS_IIN_OC_FAULT_LIMIT:
	case PMBUS_VIN_UV_WARN_LIMIT:
	case PMBUS_VIN_UV_FAULT_LIMIT:
	case PMBUS_VIN_OV_FAULT_LIMIT:
	case PMBUS_VIN_OV_WARN_LIMIT:
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_write_word_data(client, 0, reg, word);
		pmbus_clear_cache(client);
		break;
	case PMBUS_IIN_OC_WARN_LIMIT:
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_write_word_data(client, 0,
					    LM25066_MFR_IIN_OC_WARN_LIMIT,
					    word);
		pmbus_clear_cache(client);
		break;
	case PMBUS_PIN_OP_WARN_LIMIT:
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_write_word_data(client, 0,
					    LM25066_MFR_PIN_OP_WARN_LIMIT,
					    word);
		pmbus_clear_cache(client);
		break;
	case PMBUS_VIRT_VMON_UV_WARN_LIMIT:
		/* Adjust from VIN coefficients (for LM25056) */
		word = DIV_ROUND_CLOSEST((int)word * 6140, 293);
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_write_word_data(client, 0,
					    LM25056_VAUX_UV_WARN_LIMIT, word);
		pmbus_clear_cache(client);
		break;
	case PMBUS_VIRT_VMON_OV_WARN_LIMIT:
		/* Adjust from VIN coefficients (for LM25056) */
		word = DIV_ROUND_CLOSEST((int)word * 6140, 293);
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_write_word_data(client, 0,
					    LM25056_VAUX_OV_WARN_LIMIT, word);
		pmbus_clear_cache(client);
		break;
	case PMBUS_VIRT_RESET_PIN_HISTORY:
		ret = pmbus_write_byte(client, 0, LM25066_CLEAR_PIN_PEAK);
		break;
	case PMBUS_VIRT_SAMPLES:
		word = clamp_val(word, 1, LM25066_SAMPLES_FOR_AVG_MAX);
		ret = pmbus_write_byte_data(client, 0, LM25066_SAMPLES_FOR_AVG,
					    ilog2(word));
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}