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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_S3C2410 ; 
 int s3c24xxfb_probe (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2410fb_probe(struct platform_device *pdev)
{
	return s3c24xxfb_probe(pdev, DRV_S3C2410);
}