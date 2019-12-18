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
struct spi_device {int dummy; } ;
struct rmi_device_platform_data {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static inline int rmi_spi_of_probe(struct spi_device *spi,
				struct rmi_device_platform_data *pdata)
{
	return -ENODEV;
}