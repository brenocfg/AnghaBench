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
struct hackrf_dev {unsigned int sample; unsigned int sample_measured; int /*<<< orphan*/  dev; scalar_t__ jiffies_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSECS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_is_before_jiffies (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hackrf_copy_stream(struct hackrf_dev *dev, void *dst, void *src,
			       unsigned int src_len)
{
	memcpy(dst, src, src_len);

	/* calculate sample rate and output it in 10 seconds intervals */
	if (unlikely(time_is_before_jiffies(dev->jiffies_next))) {
		#define MSECS 10000UL
		unsigned int msecs = jiffies_to_msecs(jiffies -
				dev->jiffies_next + msecs_to_jiffies(MSECS));
		unsigned int samples = dev->sample - dev->sample_measured;

		dev->jiffies_next = jiffies + msecs_to_jiffies(MSECS);
		dev->sample_measured = dev->sample;
		dev_dbg(dev->dev, "slen=%u samples=%u msecs=%u sample rate=%lu\n",
				src_len, samples, msecs,
				samples * 1000UL / msecs);
	}

	/* total number of samples */
	dev->sample += src_len / 2;
}