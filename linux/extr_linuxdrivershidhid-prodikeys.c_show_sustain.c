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
struct TYPE_2__ {int midi_sustain; } ;

/* Variables and functions */
 int PCMIDI_SUSTAIN_MAX ; 
 int PCMIDI_SUSTAIN_MIN ; 
 int /*<<< orphan*/  dbg_hid (char*,int) ; 
 struct pk_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t show_sustain(struct device *dev,
 struct device_attribute *attr, char *buf)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct pk_device *pk = hid_get_drvdata(hdev);

	dbg_hid("pcmidi sysfs read sustain=%u\n", pk->pm->midi_sustain);

	return sprintf(buf, "%u (off:%u, max:%u (ms))\n", pk->pm->midi_sustain,
		PCMIDI_SUSTAIN_MIN, PCMIDI_SUSTAIN_MAX);
}