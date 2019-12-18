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
struct device_node {int dummy; } ;
struct atmel_smc_cs_conf {int /*<<< orphan*/  mode; } ;
struct atmel_ebi_dev_config {struct atmel_smc_cs_conf smcconf; } ;
struct atmel_ebi_dev {TYPE_1__* ebi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_SMC_MODE_BAT_WRITE ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_DBW_16 ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_DBW_32 ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_DBW_8 ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_EXNWMODE_FROZEN ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_EXNWMODE_READY ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_PMEN ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_PS_16 ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_PS_32 ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_PS_4 ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_PS_8 ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_READMODE_NRD ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_TDFMODE_OPTIMIZED ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE_WRITEMODE_NWE ; 
 int EINVAL ; 
 int atmel_ebi_xslate_smc_timings (struct atmel_ebi_dev*,struct device_node*,struct atmel_smc_cs_conf*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int atmel_ebi_xslate_smc_config(struct atmel_ebi_dev *ebid,
				       struct device_node *np,
				       struct atmel_ebi_dev_config *conf)
{
	struct atmel_smc_cs_conf *smcconf = &conf->smcconf;
	bool required = false;
	const char *tmp_str;
	u32 tmp;
	int ret;

	ret = of_property_read_u32(np, "atmel,smc-bus-width", &tmp);
	if (!ret) {
		switch (tmp) {
		case 8:
			smcconf->mode |= ATMEL_SMC_MODE_DBW_8;
			break;

		case 16:
			smcconf->mode |= ATMEL_SMC_MODE_DBW_16;
			break;

		case 32:
			smcconf->mode |= ATMEL_SMC_MODE_DBW_32;
			break;

		default:
			return -EINVAL;
		}

		required = true;
	}

	if (of_property_read_bool(np, "atmel,smc-tdf-optimized")) {
		smcconf->mode |= ATMEL_SMC_MODE_TDFMODE_OPTIMIZED;
		required = true;
	}

	tmp_str = NULL;
	of_property_read_string(np, "atmel,smc-byte-access-type", &tmp_str);
	if (tmp_str && !strcmp(tmp_str, "write")) {
		smcconf->mode |= ATMEL_SMC_MODE_BAT_WRITE;
		required = true;
	}

	tmp_str = NULL;
	of_property_read_string(np, "atmel,smc-read-mode", &tmp_str);
	if (tmp_str && !strcmp(tmp_str, "nrd")) {
		smcconf->mode |= ATMEL_SMC_MODE_READMODE_NRD;
		required = true;
	}

	tmp_str = NULL;
	of_property_read_string(np, "atmel,smc-write-mode", &tmp_str);
	if (tmp_str && !strcmp(tmp_str, "nwe")) {
		smcconf->mode |= ATMEL_SMC_MODE_WRITEMODE_NWE;
		required = true;
	}

	tmp_str = NULL;
	of_property_read_string(np, "atmel,smc-exnw-mode", &tmp_str);
	if (tmp_str) {
		if (!strcmp(tmp_str, "frozen"))
			smcconf->mode |= ATMEL_SMC_MODE_EXNWMODE_FROZEN;
		else if (!strcmp(tmp_str, "ready"))
			smcconf->mode |= ATMEL_SMC_MODE_EXNWMODE_READY;
		else if (strcmp(tmp_str, "disabled"))
			return -EINVAL;

		required = true;
	}

	ret = of_property_read_u32(np, "atmel,smc-page-mode", &tmp);
	if (!ret) {
		switch (tmp) {
		case 4:
			smcconf->mode |= ATMEL_SMC_MODE_PS_4;
			break;

		case 8:
			smcconf->mode |= ATMEL_SMC_MODE_PS_8;
			break;

		case 16:
			smcconf->mode |= ATMEL_SMC_MODE_PS_16;
			break;

		case 32:
			smcconf->mode |= ATMEL_SMC_MODE_PS_32;
			break;

		default:
			return -EINVAL;
		}

		smcconf->mode |= ATMEL_SMC_MODE_PMEN;
		required = true;
	}

	ret = atmel_ebi_xslate_smc_timings(ebid, np, &conf->smcconf);
	if (ret < 0)
		return -EINVAL;

	if ((ret > 0 && !required) || (!ret && required)) {
		dev_err(ebid->ebi->dev, "missing atmel,smc- properties in %pOF",
			np);
		return -EINVAL;
	}

	return required;
}