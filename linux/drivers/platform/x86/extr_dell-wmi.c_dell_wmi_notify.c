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
struct TYPE_2__ {int length; int* pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
typedef  int u16 ;
struct wmi_device {int /*<<< orphan*/  dev; } ;
struct dell_wmi_priv {scalar_t__ interface_version; } ;
typedef  int acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  dell_wmi_process_key (struct wmi_device*,int,int) ; 
 struct dell_wmi_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static void dell_wmi_notify(struct wmi_device *wdev,
			    union acpi_object *obj)
{
	struct dell_wmi_priv *priv = dev_get_drvdata(&wdev->dev);
	u16 *buffer_entry, *buffer_end;
	acpi_size buffer_size;
	int len, i;

	if (obj->type != ACPI_TYPE_BUFFER) {
		pr_warn("bad response type %x\n", obj->type);
		return;
	}

	pr_debug("Received WMI event (%*ph)\n",
		obj->buffer.length, obj->buffer.pointer);

	buffer_entry = (u16 *)obj->buffer.pointer;
	buffer_size = obj->buffer.length/2;
	buffer_end = buffer_entry + buffer_size;

	/*
	 * BIOS/ACPI on devices with WMI interface version 0 does not clear
	 * buffer before filling it. So next time when BIOS/ACPI send WMI event
	 * which is smaller as previous then it contains garbage in buffer from
	 * previous event.
	 *
	 * BIOS/ACPI on devices with WMI interface version 1 clears buffer and
	 * sometimes send more events in buffer at one call.
	 *
	 * So to prevent reading garbage from buffer we will process only first
	 * one event on devices with WMI interface version 0.
	 */
	if (priv->interface_version == 0 && buffer_entry < buffer_end)
		if (buffer_end > buffer_entry + buffer_entry[0] + 1)
			buffer_end = buffer_entry + buffer_entry[0] + 1;

	while (buffer_entry < buffer_end) {

		len = buffer_entry[0];
		if (len == 0)
			break;

		len++;

		if (buffer_entry + len > buffer_end) {
			pr_warn("Invalid length of WMI event\n");
			break;
		}

		pr_debug("Process buffer (%*ph)\n", len*2, buffer_entry);

		switch (buffer_entry[1]) {
		case 0x0000: /* One key pressed or event occurred */
			if (len > 2)
				dell_wmi_process_key(wdev, 0x0000,
						     buffer_entry[2]);
			/* Other entries could contain additional information */
			break;
		case 0x0010: /* Sequence of keys pressed */
		case 0x0011: /* Sequence of events occurred */
			for (i = 2; i < len; ++i)
				dell_wmi_process_key(wdev, buffer_entry[1],
						     buffer_entry[i]);
			break;
		default: /* Unknown event */
			pr_info("Unknown WMI event type 0x%x\n",
				(int)buffer_entry[1]);
			break;
		}

		buffer_entry += len;

	}

}