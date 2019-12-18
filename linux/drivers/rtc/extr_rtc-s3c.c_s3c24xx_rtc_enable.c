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
struct s3c_rtc {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ S3C2410_RTCCON ; 
 unsigned int S3C2410_RTCCON_CLKRST ; 
 unsigned int S3C2410_RTCCON_CNTSEL ; 
 unsigned int S3C2410_RTCCON_RTCEN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void s3c24xx_rtc_enable(struct s3c_rtc *info)
{
	unsigned int con, tmp;

	con = readw(info->base + S3C2410_RTCCON);
	/* re-enable the device, and check it is ok */
	if ((con & S3C2410_RTCCON_RTCEN) == 0) {
		dev_info(info->dev, "rtc disabled, re-enabling\n");

		tmp = readw(info->base + S3C2410_RTCCON);
		writew(tmp | S3C2410_RTCCON_RTCEN, info->base + S3C2410_RTCCON);
	}

	if (con & S3C2410_RTCCON_CNTSEL) {
		dev_info(info->dev, "removing RTCCON_CNTSEL\n");

		tmp = readw(info->base + S3C2410_RTCCON);
		writew(tmp & ~S3C2410_RTCCON_CNTSEL,
		       info->base + S3C2410_RTCCON);
	}

	if (con & S3C2410_RTCCON_CLKRST) {
		dev_info(info->dev, "removing RTCCON_CLKRST\n");

		tmp = readw(info->base + S3C2410_RTCCON);
		writew(tmp & ~S3C2410_RTCCON_CLKRST,
		       info->base + S3C2410_RTCCON);
	}
}