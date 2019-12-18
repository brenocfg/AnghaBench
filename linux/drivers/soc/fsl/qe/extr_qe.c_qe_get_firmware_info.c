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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct qe_firmware_info {int /*<<< orphan*/ * vtraps; int /*<<< orphan*/  extended_modes; int /*<<< orphan*/  id; } ;
struct property {int length; int /*<<< orphan*/ * value; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct qe_firmware_info qe_firmware_info ; 
 int qe_firmware_uploaded ; 
 struct device_node* qe_get_device_node () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

struct qe_firmware_info *qe_get_firmware_info(void)
{
	static int initialized;
	struct property *prop;
	struct device_node *qe;
	struct device_node *fw = NULL;
	const char *sprop;
	unsigned int i;

	/*
	 * If we haven't checked yet, and a driver hasn't uploaded a firmware
	 * yet, then check the device tree for information.
	 */
	if (qe_firmware_uploaded)
		return &qe_firmware_info;

	if (initialized)
		return NULL;

	initialized = 1;

	qe = qe_get_device_node();
	if (!qe)
		return NULL;

	/* Find the 'firmware' child node */
	fw = of_get_child_by_name(qe, "firmware");
	of_node_put(qe);

	/* Did we find the 'firmware' node? */
	if (!fw)
		return NULL;

	qe_firmware_uploaded = 1;

	/* Copy the data into qe_firmware_info*/
	sprop = of_get_property(fw, "id", NULL);
	if (sprop)
		strlcpy(qe_firmware_info.id, sprop,
			sizeof(qe_firmware_info.id));

	prop = of_find_property(fw, "extended-modes", NULL);
	if (prop && (prop->length == sizeof(u64))) {
		const u64 *iprop = prop->value;

		qe_firmware_info.extended_modes = *iprop;
	}

	prop = of_find_property(fw, "virtual-traps", NULL);
	if (prop && (prop->length == 32)) {
		const u32 *iprop = prop->value;

		for (i = 0; i < ARRAY_SIZE(qe_firmware_info.vtraps); i++)
			qe_firmware_info.vtraps[i] = iprop[i];
	}

	of_node_put(fw);

	return &qe_firmware_info;
}