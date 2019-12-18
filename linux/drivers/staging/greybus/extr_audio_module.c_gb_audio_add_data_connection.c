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
struct greybus_descriptor_cport {int /*<<< orphan*/  id; } ;
struct gbaudio_module_info {int /*<<< orphan*/  data_list; int /*<<< orphan*/  dev; } ;
struct gbaudio_data_connection {int /*<<< orphan*/  list; struct gb_connection* connection; int /*<<< orphan*/  data_cport; scalar_t__ id; } ;
struct gb_connection {int /*<<< orphan*/  intf_cport_id; } ;
struct gb_bundle {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_CONNECTION_FLAG_CSD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct gbaudio_data_connection*) ; 
 struct gbaudio_data_connection* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct gb_connection* gb_connection_create_offloaded (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gbaudio_module_info*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_audio_add_data_connection(struct gbaudio_module_info *gbmodule,
				struct greybus_descriptor_cport *cport_desc,
				struct gb_bundle *bundle)
{
	struct gb_connection *connection;
	struct gbaudio_data_connection *dai;

	dai = devm_kzalloc(gbmodule->dev, sizeof(*dai), GFP_KERNEL);
	if (!dai)
		return -ENOMEM;

	connection = gb_connection_create_offloaded(bundle,
						    le16_to_cpu(cport_desc->id),
						    GB_CONNECTION_FLAG_CSD);
	if (IS_ERR(connection)) {
		devm_kfree(gbmodule->dev, dai);
		return PTR_ERR(connection);
	}

	greybus_set_drvdata(bundle, gbmodule);
	dai->id = 0;
	dai->data_cport = connection->intf_cport_id;
	dai->connection = connection;
	list_add(&dai->list, &gbmodule->data_list);

	return 0;
}