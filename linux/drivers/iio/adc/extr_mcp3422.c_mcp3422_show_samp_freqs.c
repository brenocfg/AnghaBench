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
struct mcp3422 {int id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct mcp3422* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t mcp3422_show_samp_freqs(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct mcp3422 *adc = iio_priv(dev_to_iio_dev(dev));

	if (adc->id > 4)
		return sprintf(buf, "240 60 15\n");

	return sprintf(buf, "240 60 15 3\n");
}