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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct il_spectrum_notification {int dummy; } ;
struct il_priv {int measurement_status; int /*<<< orphan*/  lock; int /*<<< orphan*/  measure_report; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  measure_report ;

/* Variables and functions */
 int MEASUREMENT_READY ; 
 int PAGE_SIZE ; 
 struct il_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hex_dump_to_buffer (int /*<<< orphan*/ *,int,int,int,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (struct il_spectrum_notification*,int /*<<< orphan*/ *,int) ; 
 int min (int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int strlen (char*) ; 

__attribute__((used)) static ssize_t
il3945_show_measurement(struct device *d, struct device_attribute *attr,
			char *buf)
{
	struct il_priv *il = dev_get_drvdata(d);
	struct il_spectrum_notification measure_report;
	u32 size = sizeof(measure_report), len = 0, ofs = 0;
	u8 *data = (u8 *) &measure_report;
	unsigned long flags;

	spin_lock_irqsave(&il->lock, flags);
	if (!(il->measurement_status & MEASUREMENT_READY)) {
		spin_unlock_irqrestore(&il->lock, flags);
		return 0;
	}
	memcpy(&measure_report, &il->measure_report, size);
	il->measurement_status = 0;
	spin_unlock_irqrestore(&il->lock, flags);

	while (size && PAGE_SIZE - len) {
		hex_dump_to_buffer(data + ofs, size, 16, 1, buf + len,
				   PAGE_SIZE - len, true);
		len = strlen(buf);
		if (PAGE_SIZE - len)
			buf[len++] = '\n';

		ofs += 16;
		size -= min(size, 16U);
	}

	return len;
}