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
struct mei_device {int open_handle_count; int /*<<< orphan*/  host_clients_map; int /*<<< orphan*/  file_list; int /*<<< orphan*/  dev; } ;
struct mei_cl {int host_client_id; int /*<<< orphan*/  state; int /*<<< orphan*/  link; struct mei_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMFILE ; 
 int MEI_CLIENTS_MAX ; 
 int /*<<< orphan*/  MEI_FILE_INITIALIZING ; 
 int MEI_MAX_OPEN_HANDLE_COUNT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

int mei_cl_link(struct mei_cl *cl)
{
	struct mei_device *dev;
	int id;

	if (WARN_ON(!cl || !cl->dev))
		return -EINVAL;

	dev = cl->dev;

	id = find_first_zero_bit(dev->host_clients_map, MEI_CLIENTS_MAX);
	if (id >= MEI_CLIENTS_MAX) {
		dev_err(dev->dev, "id exceeded %d", MEI_CLIENTS_MAX);
		return -EMFILE;
	}

	if (dev->open_handle_count >= MEI_MAX_OPEN_HANDLE_COUNT) {
		dev_err(dev->dev, "open_handle_count exceeded %d",
			MEI_MAX_OPEN_HANDLE_COUNT);
		return -EMFILE;
	}

	dev->open_handle_count++;

	cl->host_client_id = id;
	list_add_tail(&cl->link, &dev->file_list);

	set_bit(id, dev->host_clients_map);

	cl->state = MEI_FILE_INITIALIZING;

	cl_dbg(dev, cl, "link cl\n");
	return 0;
}