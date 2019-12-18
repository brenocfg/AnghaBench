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
struct hfi1_devdata {int dummy; } ;
struct firmware_file {int dummy; } ;
struct css_header {int /*<<< orphan*/  exponent_size; int /*<<< orphan*/  modulus_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  module_vendor; int /*<<< orphan*/  header_version; int /*<<< orphan*/  header_len; int /*<<< orphan*/  module_type; } ;

/* Variables and functions */
 int CSS_HEADER_VERSION ; 
 int CSS_MODULE_TYPE ; 
 int CSS_MODULE_VENDOR ; 
 int EINVAL ; 
 int EXPONENT_SIZE ; 
 int KEY_SIZE ; 
 scalar_t__ invalid_header (struct hfi1_devdata*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int verify_css_header(struct hfi1_devdata *dd, struct css_header *css)
{
	/* verify CSS header fields (most sizes are in DW, so add /4) */
	if (invalid_header(dd, "module_type", css->module_type,
			   CSS_MODULE_TYPE) ||
	    invalid_header(dd, "header_len", css->header_len,
			   (sizeof(struct firmware_file) / 4)) ||
	    invalid_header(dd, "header_version", css->header_version,
			   CSS_HEADER_VERSION) ||
	    invalid_header(dd, "module_vendor", css->module_vendor,
			   CSS_MODULE_VENDOR) ||
	    invalid_header(dd, "key_size", css->key_size, KEY_SIZE / 4) ||
	    invalid_header(dd, "modulus_size", css->modulus_size,
			   KEY_SIZE / 4) ||
	    invalid_header(dd, "exponent_size", css->exponent_size,
			   EXPONENT_SIZE / 4)) {
		return -EINVAL;
	}
	return 0;
}