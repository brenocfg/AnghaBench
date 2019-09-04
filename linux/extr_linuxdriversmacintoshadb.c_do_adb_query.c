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
struct adb_request {int* data; int nbytes; int complete; int reply_len; int /*<<< orphan*/ * reply; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler_id; int /*<<< orphan*/  original_address; } ;

/* Variables and functions */
#define  ADB_QUERY_GETDEVINFO 128 
 int EINVAL ; 
 TYPE_1__* adb_handler ; 
 int /*<<< orphan*/  adb_handler_mutex ; 
 int /*<<< orphan*/  adb_write_done (struct adb_request*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_adb_query(struct adb_request *req)
{
	int	ret = -EINVAL;

	switch(req->data[1]) {
	case ADB_QUERY_GETDEVINFO:
		if (req->nbytes < 3)
			break;
		mutex_lock(&adb_handler_mutex);
		req->reply[0] = adb_handler[req->data[2]].original_address;
		req->reply[1] = adb_handler[req->data[2]].handler_id;
		mutex_unlock(&adb_handler_mutex);
		req->complete = 1;
		req->reply_len = 2;
		adb_write_done(req);
		ret = 0;
		break;
	}
	return ret;
}