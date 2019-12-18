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
typedef  scalar_t__ u16 ;
struct sgp_version {scalar_t__ major; scalar_t__ minor; } ;
struct sgp_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct sgp_version*) ; 
 int ENODEV ; 
#define  SGP30 129 
#define  SGPC3 128 
 scalar_t__ SGP_VERS_ENG_BIT (struct sgp_data*) ; 
 scalar_t__ SGP_VERS_GEN (struct sgp_data*) ; 
 scalar_t__ SGP_VERS_MAJOR (struct sgp_data*) ; 
 scalar_t__ SGP_VERS_MINOR (struct sgp_data*) ; 
 scalar_t__ SGP_VERS_PRODUCT (struct sgp_data*) ; 
 scalar_t__ SGP_VERS_RESERVED (struct sgp_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct sgp_version* supported_versions_sgp30 ; 
 struct sgp_version* supported_versions_sgpc3 ; 

__attribute__((used)) static int sgp_check_compat(struct sgp_data *data,
			    unsigned int product_id)
{
	const struct sgp_version *supported_versions;
	u16 ix, num_fs;
	u16 product, generation, major, minor;

	/* driver does not match product */
	generation = SGP_VERS_GEN(data);
	if (generation != 0) {
		dev_err(&data->client->dev,
			"incompatible product generation %d != 0", generation);
		return -ENODEV;
	}

	product = SGP_VERS_PRODUCT(data);
	if (product != product_id) {
		dev_err(&data->client->dev,
			"sensor reports a different product: 0x%04hx\n",
			product);
		return -ENODEV;
	}

	if (SGP_VERS_RESERVED(data))
		dev_warn(&data->client->dev, "reserved bit is set\n");

	/* engineering samples are not supported: no interface guarantees */
	if (SGP_VERS_ENG_BIT(data))
		return -ENODEV;

	switch (product) {
	case SGP30:
		supported_versions = supported_versions_sgp30;
		num_fs = ARRAY_SIZE(supported_versions_sgp30);
		break;
	case SGPC3:
		supported_versions = supported_versions_sgpc3;
		num_fs = ARRAY_SIZE(supported_versions_sgpc3);
		break;
	default:
		return -ENODEV;
	}

	major = SGP_VERS_MAJOR(data);
	minor = SGP_VERS_MINOR(data);
	for (ix = 0; ix < num_fs; ix++) {
		if (major == supported_versions[ix].major &&
		    minor >= supported_versions[ix].minor)
			return 0;
	}
	dev_err(&data->client->dev, "unsupported sgp version: %d.%d\n",
		major, minor);

	return -ENODEV;
}