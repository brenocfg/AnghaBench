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
struct ds1343_priv {int /*<<< orphan*/  map; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS1343_CONTROL_REG ; 
 int DS1343_EGFIL ; 
 struct ds1343_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t ds1343_show_glitchfilter(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct ds1343_priv *priv = dev_get_drvdata(dev);
	int glitch_filt_status, data;

	regmap_read(priv->map, DS1343_CONTROL_REG, &data);

	glitch_filt_status = !!(data & DS1343_EGFIL);

	if (glitch_filt_status)
		return sprintf(buf, "enabled\n");
	else
		return sprintf(buf, "disabled\n");
}