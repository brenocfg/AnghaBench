#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ipw2100_priv {int status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int index; char* desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int PAGE_SIZE ; 
 int STATUS_RF_KILL_MASK ; 
 struct ipw2100_priv* dev_get_drvdata (struct device*) ; 
 scalar_t__ ipw2100_get_ordinal (struct ipw2100_priv*,int,int*,int*) ; 
 TYPE_1__* ord_data ; 
 scalar_t__ sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t show_ordinals(struct device *d, struct device_attribute *attr,
			     char *buf)
{
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	u32 val = 0;
	int len = 0;
	u32 val_len;
	static int loop = 0;

	if (priv->status & STATUS_RF_KILL_MASK)
		return 0;

	if (loop >= ARRAY_SIZE(ord_data))
		loop = 0;

	/* sysfs provides us PAGE_SIZE buffer */
	while (len < PAGE_SIZE - 128 && loop < ARRAY_SIZE(ord_data)) {
		val_len = sizeof(u32);

		if (ipw2100_get_ordinal(priv, ord_data[loop].index, &val,
					&val_len))
			len += sprintf(buf + len, "[0x%02X] = ERROR    %s\n",
				       ord_data[loop].index,
				       ord_data[loop].desc);
		else
			len += sprintf(buf + len, "[0x%02X] = 0x%08X %s\n",
				       ord_data[loop].index, val,
				       ord_data[loop].desc);
		loop++;
	}

	return len;
}