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
struct s3c_rtc {scalar_t__ base; TYPE_1__* rtc; } ;
struct TYPE_2__ {int max_user_freq; } ;

/* Variables and functions */
 scalar_t__ S3C2410_TICNT ; 
 unsigned int S3C2410_TICNT_ENABLE ; 
 scalar_t__ S3C2443_TICNT1 ; 
 unsigned int S3C2443_TICNT1_PART (int) ; 
 unsigned int S3C2443_TICNT_PART (int) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void s3c2443_rtc_setfreq(struct s3c_rtc *info, int freq)
{
	unsigned int tmp = 0;
	int val;

	tmp = readb(info->base + S3C2410_TICNT);
	tmp &= S3C2410_TICNT_ENABLE;

	val = (info->rtc->max_user_freq / freq) - 1;

	tmp |= S3C2443_TICNT_PART(val);
	writel(S3C2443_TICNT1_PART(val), info->base + S3C2443_TICNT1);

	writel(tmp, info->base + S3C2410_TICNT);
}