#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct elan_tp_data {int pattern; int /*<<< orphan*/  ic_type; int /*<<< orphan*/  iap_version; TYPE_2__* client; int /*<<< orphan*/  fw_signature_address; int /*<<< orphan*/  fw_validpage_count; TYPE_1__* ops; int /*<<< orphan*/  pressure_adjustment; int /*<<< orphan*/  fw_checksum; int /*<<< orphan*/  fw_version; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int (* get_version ) (TYPE_2__*,int,int /*<<< orphan*/ *) ;int (* get_checksum ) (TYPE_2__*,int,int /*<<< orphan*/ *) ;int (* get_pressure_adjustment ) (TYPE_2__*,int /*<<< orphan*/ *) ;int (* get_pattern ) (TYPE_2__*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int elan_get_fwinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int stub4 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int stub5 (TYPE_2__*,int*) ; 

__attribute__((used)) static int elan_query_device_info(struct elan_tp_data *data)
{
	int error;
	u16 ic_type;

	error = data->ops->get_version(data->client, false, &data->fw_version);
	if (error)
		return error;

	error = data->ops->get_checksum(data->client, false,
					&data->fw_checksum);
	if (error)
		return error;

	error = data->ops->get_version(data->client, true, &data->iap_version);
	if (error)
		return error;

	error = data->ops->get_pressure_adjustment(data->client,
						   &data->pressure_adjustment);
	if (error)
		return error;

	error = data->ops->get_pattern(data->client, &data->pattern);
	if (error)
		return error;

	if (data->pattern == 0x01)
		ic_type = data->ic_type;
	else
		ic_type = data->iap_version;

	error = elan_get_fwinfo(ic_type, &data->fw_validpage_count,
				&data->fw_signature_address);
	if (error)
		dev_warn(&data->client->dev,
			 "unexpected iap version %#04x (ic type: %#04x), firmware update will not work\n",
			 data->iap_version, data->ic_type);

	return 0;
}