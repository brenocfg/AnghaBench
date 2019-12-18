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
struct serio {int dummy; } ;
struct rain {scalar_t__ buf_len; unsigned char* buf; size_t buf_wr_idx; int /*<<< orphan*/  work; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DATA_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct rain* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rain_interrupt(struct serio *serio, unsigned char data,
				    unsigned int flags)
{
	struct rain *rain = serio_get_drvdata(serio);

	if (rain->buf_len == DATA_SIZE) {
		dev_warn_once(rain->dev, "buffer overflow\n");
		return IRQ_HANDLED;
	}
	spin_lock(&rain->buf_lock);
	rain->buf_len++;
	rain->buf[rain->buf_wr_idx] = data;
	rain->buf_wr_idx = (rain->buf_wr_idx + 1) & 0xff;
	spin_unlock(&rain->buf_lock);
	schedule_work(&rain->work);
	return IRQ_HANDLED;
}