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
struct ishtp_cl_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_queue; } ;
struct ishtp_cl_data {int /*<<< orphan*/  work_ec_evt; int /*<<< orphan*/  work_ishtp_reset; TYPE_1__ response; struct ishtp_cl_device* cl_device; struct ishtp_cl* cros_ish_cl; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISHTP_CL_DISCONNECTING ; 
 int cros_ec_dev_init (struct ishtp_cl_data*) ; 
 int cros_ish_init (struct ishtp_cl*) ; 
 struct ishtp_cl_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_lock ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ish_evt_handler ; 
 struct ishtp_cl* ishtp_cl_allocate (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_cl_disconnect (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_flush_queues (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_free (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_unlink (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_device (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_get_device (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_put_device (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_set_client_data (struct ishtp_cl*,struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  ishtp_set_connection_state (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_set_drvdata (struct ishtp_cl_device*,struct ishtp_cl*) ; 
 int /*<<< orphan*/  reset_handler ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_ishtp_probe(struct ishtp_cl_device *cl_device)
{
	int rv;
	struct ishtp_cl *cros_ish_cl;
	struct ishtp_cl_data *client_data =
		devm_kzalloc(ishtp_device(cl_device),
			     sizeof(*client_data), GFP_KERNEL);
	if (!client_data)
		return -ENOMEM;

	/* Lock for initialization to complete */
	down_write(&init_lock);

	cros_ish_cl = ishtp_cl_allocate(cl_device);
	if (!cros_ish_cl) {
		rv = -ENOMEM;
		goto end_ishtp_cl_alloc_error;
	}

	ishtp_set_drvdata(cl_device, cros_ish_cl);
	ishtp_set_client_data(cros_ish_cl, client_data);
	client_data->cros_ish_cl = cros_ish_cl;
	client_data->cl_device = cl_device;

	init_waitqueue_head(&client_data->response.wait_queue);

	INIT_WORK(&client_data->work_ishtp_reset,
		  reset_handler);
	INIT_WORK(&client_data->work_ec_evt,
		  ish_evt_handler);

	rv = cros_ish_init(cros_ish_cl);
	if (rv)
		goto end_ishtp_cl_init_error;

	ishtp_get_device(cl_device);

	up_write(&init_lock);

	/* Register croc_ec_dev mfd */
	rv = cros_ec_dev_init(client_data);
	if (rv)
		goto end_cros_ec_dev_init_error;

	return 0;

end_cros_ec_dev_init_error:
	ishtp_set_connection_state(cros_ish_cl, ISHTP_CL_DISCONNECTING);
	ishtp_cl_disconnect(cros_ish_cl);
	ishtp_cl_unlink(cros_ish_cl);
	ishtp_cl_flush_queues(cros_ish_cl);
	ishtp_put_device(cl_device);
end_ishtp_cl_init_error:
	ishtp_cl_free(cros_ish_cl);
end_ishtp_cl_alloc_error:
	up_write(&init_lock);
	return rv;
}