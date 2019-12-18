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
struct TYPE_2__ {int midi_octave; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int PCMIDI_OCTAVE_MAX ; 
 int PCMIDI_OCTAVE_MIN ; 
 int /*<<< orphan*/  dbg_hid (char*,int) ; 
 struct pk_device* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t store_octave(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct pk_device *pk = hid_get_drvdata(hdev);

	int octave = 0;

	if (sscanf(buf, "%d", &octave) > 0 &&
		octave >= PCMIDI_OCTAVE_MIN && octave <= PCMIDI_OCTAVE_MAX) {
		dbg_hid("pcmidi sysfs write octave=%d\n", octave);
		pk->pm->midi_octave = octave;
		return strlen(buf);
	}
	return -EINVAL;
}