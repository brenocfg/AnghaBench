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
typedef  int /*<<< orphan*/  u32 ;
struct scmi_power_info {int num_domains; struct power_dom_info* dom_info; } ;
struct scmi_handle {struct scmi_power_info* power_priv; int /*<<< orphan*/ * power_ops; int /*<<< orphan*/  dev; } ;
struct power_dom_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PROTOCOL_REV_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTOCOL_REV_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_POWER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct power_dom_info* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct scmi_power_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_ops ; 
 int /*<<< orphan*/  scmi_power_attributes_get (struct scmi_handle*,struct scmi_power_info*) ; 
 int /*<<< orphan*/  scmi_power_domain_attributes_get (struct scmi_handle*,int,struct power_dom_info*) ; 
 int /*<<< orphan*/  scmi_version_get (struct scmi_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scmi_power_protocol_init(struct scmi_handle *handle)
{
	int domain;
	u32 version;
	struct scmi_power_info *pinfo;

	scmi_version_get(handle, SCMI_PROTOCOL_POWER, &version);

	dev_dbg(handle->dev, "Power Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	pinfo = devm_kzalloc(handle->dev, sizeof(*pinfo), GFP_KERNEL);
	if (!pinfo)
		return -ENOMEM;

	scmi_power_attributes_get(handle, pinfo);

	pinfo->dom_info = devm_kcalloc(handle->dev, pinfo->num_domains,
				       sizeof(*pinfo->dom_info), GFP_KERNEL);
	if (!pinfo->dom_info)
		return -ENOMEM;

	for (domain = 0; domain < pinfo->num_domains; domain++) {
		struct power_dom_info *dom = pinfo->dom_info + domain;

		scmi_power_domain_attributes_get(handle, domain, dom);
	}

	handle->power_ops = &power_ops;
	handle->power_priv = pinfo;

	return 0;
}