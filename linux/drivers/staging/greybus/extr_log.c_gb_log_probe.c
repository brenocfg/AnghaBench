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
struct greybus_descriptor_cport {scalar_t__ protocol_id; int /*<<< orphan*/  id; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_log {struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct gb_bundle {int num_cports; struct greybus_descriptor_cport* cport_desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GREYBUS_PROTOCOL_LOG ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 struct gb_connection* gb_connection_create (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_log_request_handler ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gb_log*) ; 
 int /*<<< orphan*/  kfree (struct gb_log*) ; 
 struct gb_log* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_log_probe(struct gb_bundle *bundle,
			const struct greybus_bundle_id *id)
{
	struct greybus_descriptor_cport *cport_desc;
	struct gb_connection *connection;
	struct gb_log *log;
	int retval;

	if (bundle->num_cports != 1)
		return -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	if (cport_desc->protocol_id != GREYBUS_PROTOCOL_LOG)
		return -ENODEV;

	log = kzalloc(sizeof(*log), GFP_KERNEL);
	if (!log)
		return -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_log_request_handler);
	if (IS_ERR(connection)) {
		retval = PTR_ERR(connection);
		goto error_free;
	}

	log->connection = connection;
	greybus_set_drvdata(bundle, log);

	retval = gb_connection_enable(connection);
	if (retval)
		goto error_connection_destroy;

	return 0;

error_connection_destroy:
	gb_connection_destroy(connection);
error_free:
	kfree(log);
	return retval;
}