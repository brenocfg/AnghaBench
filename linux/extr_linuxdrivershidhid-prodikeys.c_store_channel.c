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
struct pk_device {TYPE_1__* pm; } ;
struct hid_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {unsigned int midi_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 unsigned int PCMIDI_CHANNEL_MAX ; 
 int /*<<< orphan*/  dbg_hid (char*,unsigned int) ; 
 struct pk_device* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ sscanf (char const*,char*,unsigned int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t store_channel(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct pk_device *pk = hid_get_drvdata(hdev);

	unsigned channel = 0;

	if (sscanf(buf, "%u", &channel) > 0 && channel <= PCMIDI_CHANNEL_MAX) {
		dbg_hid("pcmidi sysfs write channel=%u\n", channel);
		pk->pm->midi_channel = channel;
		return strlen(buf);
	}
	return -EINVAL;
}