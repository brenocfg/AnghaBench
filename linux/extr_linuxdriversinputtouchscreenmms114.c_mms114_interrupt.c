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
typedef  int /*<<< orphan*/  u8 ;
struct mms114_touch {int dummy; } ;
struct mms114_data {struct input_dev* input_dev; } ;
struct input_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  users; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MMS114_INFORMATION ; 
 int MMS114_MAX_TOUCH ; 
 int MMS114_PACKET_NUM ; 
 int /*<<< orphan*/  MMS114_PACKET_SIZE ; 
 int __mms114_read_reg (struct mms114_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_mt_report_pointer_emulation (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mms114_process_mt (struct mms114_data*,struct mms114_touch*) ; 
 int mms114_read_reg (struct mms114_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mms114_interrupt(int irq, void *dev_id)
{
	struct mms114_data *data = dev_id;
	struct input_dev *input_dev = data->input_dev;
	struct mms114_touch touch[MMS114_MAX_TOUCH];
	int packet_size;
	int touch_size;
	int index;
	int error;

	mutex_lock(&input_dev->mutex);
	if (!input_dev->users) {
		mutex_unlock(&input_dev->mutex);
		goto out;
	}
	mutex_unlock(&input_dev->mutex);

	packet_size = mms114_read_reg(data, MMS114_PACKET_SIZE);
	if (packet_size <= 0)
		goto out;

	touch_size = packet_size / MMS114_PACKET_NUM;

	error = __mms114_read_reg(data, MMS114_INFORMATION, packet_size,
			(u8 *)touch);
	if (error < 0)
		goto out;

	for (index = 0; index < touch_size; index++)
		mms114_process_mt(data, touch + index);

	input_mt_report_pointer_emulation(data->input_dev, true);
	input_sync(data->input_dev);

out:
	return IRQ_HANDLED;
}