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

/* Variables and functions */

__attribute__((used)) static inline void s3c64xx_onenand1_setname(char *name)
{
#ifdef CONFIG_S3C64XX_DEV_ONENAND1
	s3c64xx_device_onenand1.name = name;
#endif
}