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
struct rc_dev {struct nvt_dev* priv; } ;
struct nvt_dev {int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BUF_LEN_MASK ; 
 int /*<<< orphan*/  CIR_WAKE_FIFO_COUNT ; 
 int /*<<< orphan*/  CIR_WAKE_RD_FIFO_ONLY ; 
 int /*<<< orphan*/  CIR_WAKE_RD_FIFO_ONLY_IDX ; 
 int PAGE_SIZE ; 
 int SAMPLE_PERIOD ; 
 int /*<<< orphan*/  WAKEUP_MAX_SIZE ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int nvt_cir_wake_reg_read (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rc_dev* to_rc_dev (struct device*) ; 

__attribute__((used)) static ssize_t wakeup_data_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct rc_dev *rc_dev = to_rc_dev(dev);
	struct nvt_dev *nvt = rc_dev->priv;
	int fifo_len, duration;
	unsigned long flags;
	ssize_t buf_len = 0;
	int i;

	spin_lock_irqsave(&nvt->lock, flags);

	fifo_len = nvt_cir_wake_reg_read(nvt, CIR_WAKE_FIFO_COUNT);
	fifo_len = min(fifo_len, WAKEUP_MAX_SIZE);

	/* go to first element to be read */
	while (nvt_cir_wake_reg_read(nvt, CIR_WAKE_RD_FIFO_ONLY_IDX))
		nvt_cir_wake_reg_read(nvt, CIR_WAKE_RD_FIFO_ONLY);

	for (i = 0; i < fifo_len; i++) {
		duration = nvt_cir_wake_reg_read(nvt, CIR_WAKE_RD_FIFO_ONLY);
		duration = (duration & BUF_LEN_MASK) * SAMPLE_PERIOD;
		buf_len += snprintf(buf + buf_len, PAGE_SIZE - buf_len,
				    "%d ", duration);
	}
	buf_len += snprintf(buf + buf_len, PAGE_SIZE - buf_len, "\n");

	spin_unlock_irqrestore(&nvt->lock, flags);

	return buf_len;
}