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
struct airspy {scalar_t__ pixelformat; unsigned int sample; unsigned int sample_measured; int /*<<< orphan*/  dev; scalar_t__ jiffies_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSECS ; 
 scalar_t__ V4L2_SDR_FMT_RU12LE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_is_before_jiffies (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int airspy_convert_stream(struct airspy *s,
		void *dst, void *src, unsigned int src_len)
{
	unsigned int dst_len;

	if (s->pixelformat == V4L2_SDR_FMT_RU12LE) {
		memcpy(dst, src, src_len);
		dst_len = src_len;
	} else {
		dst_len = 0;
	}

	/* calculate sample rate and output it in 10 seconds intervals */
	if (unlikely(time_is_before_jiffies(s->jiffies_next))) {
		#define MSECS 10000UL
		unsigned int msecs = jiffies_to_msecs(jiffies -
				s->jiffies_next + msecs_to_jiffies(MSECS));
		unsigned int samples = s->sample - s->sample_measured;

		s->jiffies_next = jiffies + msecs_to_jiffies(MSECS);
		s->sample_measured = s->sample;
		dev_dbg(s->dev, "slen=%u samples=%u msecs=%u sample rate=%lu\n",
				src_len, samples, msecs,
				samples * 1000UL / msecs);
	}

	/* total number of samples */
	s->sample += src_len / 2;

	return dst_len;
}