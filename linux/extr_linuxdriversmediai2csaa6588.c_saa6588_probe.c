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
struct v4l2_subdev {int dummy; } ;
struct saa6588 {int buf_size; int last_blocknum; int /*<<< orphan*/  work; scalar_t__ data_available_for_read; int /*<<< orphan*/  read_queue; scalar_t__ rd_index; scalar_t__ wr_index; scalar_t__ block_count; int /*<<< orphan*/  lock; struct v4l2_subdev sd; int /*<<< orphan*/ * buffer; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bufblocks ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa6588_configure (struct saa6588*) ; 
 int /*<<< orphan*/  saa6588_ops ; 
 int /*<<< orphan*/  saa6588_work ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa6588_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct saa6588 *s;
	struct v4l2_subdev *sd;

	v4l_info(client, "saa6588 found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	s = devm_kzalloc(&client->dev, sizeof(*s), GFP_KERNEL);
	if (s == NULL)
		return -ENOMEM;

	s->buf_size = bufblocks * 3;

	s->buffer = devm_kzalloc(&client->dev, s->buf_size, GFP_KERNEL);
	if (s->buffer == NULL)
		return -ENOMEM;
	sd = &s->sd;
	v4l2_i2c_subdev_init(sd, client, &saa6588_ops);
	spin_lock_init(&s->lock);
	s->block_count = 0;
	s->wr_index = 0;
	s->rd_index = 0;
	s->last_blocknum = 0xff;
	init_waitqueue_head(&s->read_queue);
	s->data_available_for_read = 0;

	saa6588_configure(s);

	/* start polling via eventd */
	INIT_DELAYED_WORK(&s->work, saa6588_work);
	schedule_delayed_work(&s->work, 0);
	return 0;
}