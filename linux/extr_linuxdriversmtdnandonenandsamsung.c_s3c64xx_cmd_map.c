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
 unsigned int S3C64XX_CMD_MAP_SHIFT ; 

__attribute__((used)) static unsigned int s3c64xx_cmd_map(unsigned type, unsigned val)
{
	return (type << S3C64XX_CMD_MAP_SHIFT) | val;
}