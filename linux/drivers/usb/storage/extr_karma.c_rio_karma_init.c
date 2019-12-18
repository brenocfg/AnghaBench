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
struct us_data {int /*<<< orphan*/  extra_destructor; struct karma_data* extra; } ;
struct karma_data {int in_storage; int /*<<< orphan*/  recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  RIO_ENTER_STORAGE ; 
 int /*<<< orphan*/  RIO_RECV_LEN ; 
 int /*<<< orphan*/  kfree (struct karma_data*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct karma_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_karma_destructor ; 
 int rio_karma_send_command (int /*<<< orphan*/ ,struct us_data*) ; 

__attribute__((used)) static int rio_karma_init(struct us_data *us)
{
	int ret = 0;
	struct karma_data *data = kzalloc(sizeof(struct karma_data), GFP_NOIO);

	if (!data)
		goto out;

	data->recv = kmalloc(RIO_RECV_LEN, GFP_NOIO);
	if (!data->recv) {
		kfree(data);
		goto out;
	}

	us->extra = data;
	us->extra_destructor = rio_karma_destructor;
	ret = rio_karma_send_command(RIO_ENTER_STORAGE, us);
	data->in_storage = (ret == 0);
out:
	return ret;
}