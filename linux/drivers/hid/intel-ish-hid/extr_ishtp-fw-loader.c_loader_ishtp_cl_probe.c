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
struct ishtp_cl_data {int /*<<< orphan*/  work_fw_load; scalar_t__ retry_count; int /*<<< orphan*/  work_ishtp_reset; TYPE_1__ response; struct ishtp_cl_device* cl_device; struct ishtp_cl* loader_ishtp_cl; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ishtp_cl_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ishtp_cl* ishtp_cl_allocate (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_cl_free (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_device (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_get_device (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_set_client_data (struct ishtp_cl*,struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  ishtp_set_drvdata (struct ishtp_cl_device*,struct ishtp_cl*) ; 
 int /*<<< orphan*/  load_fw_from_host_handler ; 
 int loader_init (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_handler ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loader_ishtp_cl_probe(struct ishtp_cl_device *cl_device)
{
	struct ishtp_cl *loader_ishtp_cl;
	struct ishtp_cl_data *client_data;
	int rv;

	client_data = devm_kzalloc(ishtp_device(cl_device),
				   sizeof(*client_data),
				   GFP_KERNEL);
	if (!client_data)
		return -ENOMEM;

	loader_ishtp_cl = ishtp_cl_allocate(cl_device);
	if (!loader_ishtp_cl)
		return -ENOMEM;

	ishtp_set_drvdata(cl_device, loader_ishtp_cl);
	ishtp_set_client_data(loader_ishtp_cl, client_data);
	client_data->loader_ishtp_cl = loader_ishtp_cl;
	client_data->cl_device = cl_device;

	init_waitqueue_head(&client_data->response.wait_queue);

	INIT_WORK(&client_data->work_ishtp_reset,
		  reset_handler);
	INIT_WORK(&client_data->work_fw_load,
		  load_fw_from_host_handler);

	rv = loader_init(loader_ishtp_cl, 0);
	if (rv < 0) {
		ishtp_cl_free(loader_ishtp_cl);
		return rv;
	}
	ishtp_get_device(cl_device);

	client_data->retry_count = 0;

	/* ISH firmware loading from host */
	schedule_work(&client_data->work_fw_load);

	return 0;
}