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
struct gbaudio_module_info {struct gb_connection* mgmt_connection; } ;
struct gb_connection {int dummy; } ;
struct gb_bundle {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gb_connection* gb_connection_create (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbaudio_codec_request_handler ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gbaudio_module_info*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_audio_add_mgmt_connection(struct gbaudio_module_info *gbmodule,
				struct greybus_descriptor_cport *cport_desc,
				struct gb_bundle *bundle)
{
	struct gb_connection *connection;

	/* Management Cport */
	if (gbmodule->mgmt_connection) {
		dev_err(&bundle->dev,
			"Can't have multiple Management connections\n");
		return -ENODEV;
	}

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gbaudio_codec_request_handler);
	if (IS_ERR(connection))
		return PTR_ERR(connection);

	greybus_set_drvdata(bundle, gbmodule);
	gbmodule->mgmt_connection = connection;

	return 0;
}