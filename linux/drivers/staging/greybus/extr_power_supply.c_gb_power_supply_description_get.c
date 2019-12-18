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
struct gb_power_supply_get_description_response {int /*<<< orphan*/  properties_count; int /*<<< orphan*/  type; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model; int /*<<< orphan*/  manufacturer; } ;
struct gb_power_supply_get_description_request {int /*<<< orphan*/  psy_id; } ;
struct gb_power_supply {int /*<<< orphan*/  properties_count; int /*<<< orphan*/  type; void* serial_number; void* model_name; void* manufacturer; int /*<<< orphan*/  id; } ;
struct gb_connection {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_POWER_SUPPLY_TYPE_GET_DESCRIPTION ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PROP_MAX ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_power_supply_get_description_request*,int,struct gb_power_supply_get_description_response*,int) ; 
 struct gb_connection* get_conn_from_psy (struct gb_power_supply*) ; 
 void* kstrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_power_supply_description_get(struct gb_power_supply *gbpsy)
{
	struct gb_connection *connection = get_conn_from_psy(gbpsy);
	struct gb_power_supply_get_description_request req;
	struct gb_power_supply_get_description_response resp;
	int ret;

	req.psy_id = gbpsy->id;

	ret = gb_operation_sync(connection,
				GB_POWER_SUPPLY_TYPE_GET_DESCRIPTION,
				&req, sizeof(req), &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	gbpsy->manufacturer = kstrndup(resp.manufacturer, PROP_MAX, GFP_KERNEL);
	if (!gbpsy->manufacturer)
		return -ENOMEM;
	gbpsy->model_name = kstrndup(resp.model, PROP_MAX, GFP_KERNEL);
	if (!gbpsy->model_name)
		return -ENOMEM;
	gbpsy->serial_number = kstrndup(resp.serial_number, PROP_MAX,
				       GFP_KERNEL);
	if (!gbpsy->serial_number)
		return -ENOMEM;

	gbpsy->type = le16_to_cpu(resp.type);
	gbpsy->properties_count = resp.properties_count;

	return 0;
}