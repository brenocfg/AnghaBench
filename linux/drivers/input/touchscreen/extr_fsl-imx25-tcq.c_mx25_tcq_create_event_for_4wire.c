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
typedef  int /*<<< orphan*/  u32 ;
struct mx25_tcq_priv {unsigned int pen_threshold; unsigned int sample_count; int /*<<< orphan*/  idev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 unsigned int MX25_ADCQ_FIFO_DATA (int /*<<< orphan*/ ) ; 
 unsigned int MX25_ADCQ_FIFO_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx25_tcq_enable_fifo_irq (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  mx25_tcq_re_enable_touch_detection (struct mx25_tcq_priv*) ; 

__attribute__((used)) static void mx25_tcq_create_event_for_4wire(struct mx25_tcq_priv *priv,
					    u32 *sample_buf,
					    unsigned int samples)
{
	unsigned int x_pos = 0;
	unsigned int y_pos = 0;
	unsigned int touch_pre = 0;
	unsigned int touch_post = 0;
	unsigned int i;

	for (i = 0; i < samples; i++) {
		unsigned int index = MX25_ADCQ_FIFO_ID(sample_buf[i]);
		unsigned int val = MX25_ADCQ_FIFO_DATA(sample_buf[i]);

		switch (index) {
		case 1:
			touch_pre = val;
			break;
		case 2:
			x_pos = val;
			break;
		case 3:
			y_pos = val;
			break;
		case 5:
			touch_post = val;
			break;
		default:
			dev_dbg(priv->dev, "Dropped samples because of invalid index %d\n",
				index);
			return;
		}
	}

	if (samples != 0) {
		/*
		 * only if both touch measures are below a threshold,
		 * the position is valid
		 */
		if (touch_pre < priv->pen_threshold &&
		    touch_post < priv->pen_threshold) {
			/* valid samples, generate a report */
			x_pos /= priv->sample_count;
			y_pos /= priv->sample_count;
			input_report_abs(priv->idev, ABS_X, x_pos);
			input_report_abs(priv->idev, ABS_Y, y_pos);
			input_report_key(priv->idev, BTN_TOUCH, 1);
			input_sync(priv->idev);

			/* get next sample */
			mx25_tcq_enable_fifo_irq(priv);
		} else if (touch_pre >= priv->pen_threshold &&
			   touch_post >= priv->pen_threshold) {
			/*
			 * if both samples are invalid,
			 * generate a release report
			 */
			input_report_key(priv->idev, BTN_TOUCH, 0);
			input_sync(priv->idev);
			mx25_tcq_re_enable_touch_detection(priv);
		} else {
			/*
			 * if only one of both touch measurements are
			 * below the threshold, still some bouncing
			 * happens. Take additional samples in this
			 * case to be sure
			 */
			mx25_tcq_enable_fifo_irq(priv);
		}
	}
}