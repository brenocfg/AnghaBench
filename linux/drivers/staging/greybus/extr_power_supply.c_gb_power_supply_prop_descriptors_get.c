#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct gb_power_supply_get_property_descriptors_response {TYPE_4__* props; } ;
struct gb_power_supply_get_property_descriptors_request {int /*<<< orphan*/  psy_id; } ;
struct gb_power_supply {int properties_count; int* props_raw; TYPE_5__* props; int /*<<< orphan*/  id; } ;
struct gb_operation {TYPE_2__* response; TYPE_1__* request; } ;
struct gb_connection {TYPE_3__* bundle; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_10__ {int prop; int is_writeable; int /*<<< orphan*/  gb_prop; } ;
struct TYPE_9__ {scalar_t__ is_writeable; int /*<<< orphan*/  property; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct gb_power_supply_get_property_descriptors_response* payload; } ;
struct TYPE_6__ {struct gb_power_supply_get_property_descriptors_request* payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_POWER_SUPPLY_TYPE_GET_PROP_DESCRIPTORS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _gb_power_supply_append_props (struct gb_power_supply*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct gb_operation* gb_operation_create (struct gb_connection*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send_sync (struct gb_operation*) ; 
 struct gb_connection* get_conn_from_psy (struct gb_power_supply*) ; 
 int get_psp_from_gb_prop (int /*<<< orphan*/ ,int*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  props ; 
 int /*<<< orphan*/  struct_size (struct gb_power_supply_get_property_descriptors_response*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gb_power_supply_prop_descriptors_get(struct gb_power_supply *gbpsy)
{
	struct gb_connection *connection = get_conn_from_psy(gbpsy);
	struct gb_power_supply_get_property_descriptors_request *req;
	struct gb_power_supply_get_property_descriptors_response *resp;
	struct gb_operation *op;
	u8 props_count = gbpsy->properties_count;
	enum power_supply_property psp;
	int ret;
	int i, r = 0;

	if (props_count == 0)
		return 0;

	op = gb_operation_create(connection,
				 GB_POWER_SUPPLY_TYPE_GET_PROP_DESCRIPTORS,
				 sizeof(*req),
				 struct_size(resp, props, props_count),
				 GFP_KERNEL);
	if (!op)
		return -ENOMEM;

	req = op->request->payload;
	req->psy_id = gbpsy->id;

	ret = gb_operation_request_send_sync(op);
	if (ret < 0)
		goto out_put_operation;

	resp = op->response->payload;

	/* validate received properties */
	for (i = 0; i < props_count; i++) {
		ret = get_psp_from_gb_prop(resp->props[i].property, &psp);
		if (ret < 0) {
			dev_warn(&connection->bundle->dev,
				 "greybus property %u it is not supported by this kernel, dropped\n",
				 resp->props[i].property);
			gbpsy->properties_count--;
		}
	}

	gbpsy->props = kcalloc(gbpsy->properties_count, sizeof(*gbpsy->props),
			      GFP_KERNEL);
	if (!gbpsy->props) {
		ret = -ENOMEM;
		goto out_put_operation;
	}

	gbpsy->props_raw = kcalloc(gbpsy->properties_count,
				   sizeof(*gbpsy->props_raw), GFP_KERNEL);
	if (!gbpsy->props_raw) {
		ret = -ENOMEM;
		goto out_put_operation;
	}

	/* Store available properties, skip the ones we do not support */
	for (i = 0; i < props_count; i++) {
		ret = get_psp_from_gb_prop(resp->props[i].property, &psp);
		if (ret < 0) {
			r++;
			continue;
		}
		gbpsy->props[i - r].prop = psp;
		gbpsy->props[i - r].gb_prop = resp->props[i].property;
		gbpsy->props_raw[i - r] = psp;
		if (resp->props[i].is_writeable)
			gbpsy->props[i - r].is_writeable = true;
	}

	/*
	 * now append the properties that we already got information in the
	 * get_description operation. (char * ones)
	 */
	_gb_power_supply_append_props(gbpsy);

	ret = 0;
out_put_operation:
	gb_operation_put(op);

	return ret;
}