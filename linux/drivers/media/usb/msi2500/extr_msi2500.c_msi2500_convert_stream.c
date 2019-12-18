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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct msi2500_dev {int next_sample; int pixelformat; unsigned int sample; int /*<<< orphan*/  dev; scalar_t__ jiffies_next; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSECS ; 
#define  MSI2500_PIX_FMT_SDR_MSI2500_384 133 
#define  MSI2500_PIX_FMT_SDR_S12 132 
#define  V4L2_SDR_FMT_CS14LE 131 
#define  V4L2_SDR_FMT_CS8 130 
#define  V4L2_SDR_FMT_CU16LE 129 
#define  V4L2_SDR_FMT_CU8 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_is_before_jiffies (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msi2500_convert_stream(struct msi2500_dev *dev, u8 *dst, u8 *src,
				  unsigned int src_len)
{
	unsigned int i, j, transactions, dst_len = 0;
	u32 sample[3];

	/* There could be 1-3 1024 byte transactions per packet */
	transactions = src_len / 1024;

	for (i = 0; i < transactions; i++) {
		sample[i] = src[3] << 24 | src[2] << 16 | src[1] << 8 |
				src[0] << 0;
		if (i == 0 && dev->next_sample != sample[0]) {
			dev_dbg_ratelimited(dev->dev,
					    "%d samples lost, %d %08x:%08x\n",
					    sample[0] - dev->next_sample,
					    src_len, dev->next_sample,
					    sample[0]);
		}

		/*
		 * Dump all unknown 'garbage' data - maybe we will discover
		 * someday if there is something rational...
		 */
		dev_dbg_ratelimited(dev->dev, "%*ph\n", 12, &src[4]);

		src += 16; /* skip header */

		switch (dev->pixelformat) {
		case V4L2_SDR_FMT_CU8: /* 504 x IQ samples */
		{
			s8 *s8src = (s8 *)src;
			u8 *u8dst = (u8 *)dst;

			for (j = 0; j < 1008; j++)
				*u8dst++ = *s8src++ + 128;

			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 504;
			break;
		}
		case  V4L2_SDR_FMT_CU16LE: /* 252 x IQ samples */
		{
			s16 *s16src = (s16 *)src;
			u16 *u16dst = (u16 *)dst;
			struct {signed int x:14; } se; /* sign extension */
			unsigned int utmp;

			for (j = 0; j < 1008; j += 2) {
				/* sign extension from 14-bit to signed int */
				se.x = *s16src++;
				/* from signed int to unsigned int */
				utmp = se.x + 8192;
				/* from 14-bit to 16-bit */
				*u16dst++ = utmp << 2 | utmp >> 12;
			}

			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 252;
			break;
		}
		case MSI2500_PIX_FMT_SDR_MSI2500_384: /* 384 x IQ samples */
			/* Dump unknown 'garbage' data */
			dev_dbg_ratelimited(dev->dev, "%*ph\n", 24, &src[1000]);
			memcpy(dst, src, 984);
			src += 984 + 24;
			dst += 984;
			dst_len += 984;
			dev->next_sample = sample[i] + 384;
			break;
		case V4L2_SDR_FMT_CS8:         /* 504 x IQ samples */
			memcpy(dst, src, 1008);
			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 504;
			break;
		case MSI2500_PIX_FMT_SDR_S12:  /* 336 x IQ samples */
			memcpy(dst, src, 1008);
			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 336;
			break;
		case V4L2_SDR_FMT_CS14LE:      /* 252 x IQ samples */
			memcpy(dst, src, 1008);
			src += 1008;
			dst += 1008;
			dst_len += 1008;
			dev->next_sample = sample[i] + 252;
			break;
		default:
			break;
		}
	}

	/* calculate sample rate and output it in 10 seconds intervals */
	if (unlikely(time_is_before_jiffies(dev->jiffies_next))) {
		#define MSECS 10000UL
		unsigned int msecs = jiffies_to_msecs(jiffies -
				dev->jiffies_next + msecs_to_jiffies(MSECS));
		unsigned int samples = dev->next_sample - dev->sample;

		dev->jiffies_next = jiffies + msecs_to_jiffies(MSECS);
		dev->sample = dev->next_sample;
		dev_dbg(dev->dev, "size=%u samples=%u msecs=%u sample rate=%lu\n",
			src_len, samples, msecs,
			samples * 1000UL / msecs);
	}

	return dst_len;
}