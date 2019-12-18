#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct asus_wmi {int spec; int sfun; int wmi_event_queue; TYPE_3__* driver; int /*<<< orphan*/  dsts_id; TYPE_1__* platform_device; } ;
struct TYPE_6__ {TYPE_2__* quirks; int /*<<< orphan*/  event_guid; } ;
struct TYPE_5__ {scalar_t__ wapf; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_ACPI_UID_ASUSWMI ; 
 int /*<<< orphan*/  ASUS_ACPI_UID_ATK ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_CWAP ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_DCTS ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_DSTS ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_INIT ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_SFUN ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_SPEC ; 
 int /*<<< orphan*/  ASUS_WMI_MGMT_GUID ; 
 int ENODEV ; 
 int /*<<< orphan*/  asus_wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  asus_wmi_notify_queue_flush (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_set_devstate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* wmi_get_acpi_device_uid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_wmi_platform_init(struct asus_wmi *asus)
{
	struct device *dev = &asus->platform_device->dev;
	char *wmi_uid;
	int rv;

	/* INIT enable hotkeys on some models */
	if (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_INIT, 0, 0, &rv))
		pr_info("Initialization: %#x\n", rv);

	/* We don't know yet what to do with this version... */
	if (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_SPEC, 0, 0x9, &rv)) {
		pr_info("BIOS WMI version: %d.%d\n", rv >> 16, rv & 0xFF);
		asus->spec = rv;
	}

	/*
	 * The SFUN method probably allows the original driver to get the list
	 * of features supported by a given model. For now, 0x0100 or 0x0800
	 * bit signifies that the laptop is equipped with a Wi-Fi MiniPCI card.
	 * The significance of others is yet to be found.
	 */
	if (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_SFUN, 0, 0, &rv)) {
		pr_info("SFUN value: %#x\n", rv);
		asus->sfun = rv;
	}

	/*
	 * Eee PC and Notebooks seems to have different method_id for DSTS,
	 * but it may also be related to the BIOS's SPEC.
	 * Note, on most Eeepc, there is no way to check if a method exist
	 * or note, while on notebooks, they returns 0xFFFFFFFE on failure,
	 * but once again, SPEC may probably be used for that kind of things.
	 *
	 * Additionally at least TUF Gaming series laptops return nothing for
	 * unknown methods, so the detection in this way is not possible.
	 *
	 * There is strong indication that only ACPI WMI devices that have _UID
	 * equal to "ASUSWMI" use DCTS whereas those with "ATK" use DSTS.
	 */
	wmi_uid = wmi_get_acpi_device_uid(ASUS_WMI_MGMT_GUID);
	if (!wmi_uid)
		return -ENODEV;

	if (!strcmp(wmi_uid, ASUS_ACPI_UID_ASUSWMI)) {
		dev_info(dev, "Detected ASUSWMI, use DCTS\n");
		asus->dsts_id = ASUS_WMI_METHODID_DCTS;
	} else {
		dev_info(dev, "Detected %s, not ASUSWMI, use DSTS\n", wmi_uid);
		asus->dsts_id = ASUS_WMI_METHODID_DSTS;
	}

	/*
	 * Some devices can have multiple event codes stored in a queue before
	 * the module load if it was unloaded intermittently after calling
	 * the INIT method (enables event handling). The WMI notify handler is
	 * expected to retrieve all event codes until a retrieved code equals
	 * queue end marker (One or Ones). Old codes are flushed from the queue
	 * upon module load. Not enabling this when it should be has minimal
	 * visible impact so fall back if anything goes wrong.
	 */
	wmi_uid = wmi_get_acpi_device_uid(asus->driver->event_guid);
	if (wmi_uid && !strcmp(wmi_uid, ASUS_ACPI_UID_ATK)) {
		dev_info(dev, "Detected ATK, enable event queue\n");

		if (!asus_wmi_notify_queue_flush(asus))
			asus->wmi_event_queue = true;
	}

	/* CWAP allow to define the behavior of the Fn+F2 key,
	 * this method doesn't seems to be present on Eee PCs */
	if (asus->driver->quirks->wapf >= 0)
		asus_wmi_set_devstate(ASUS_WMI_DEVID_CWAP,
				      asus->driver->quirks->wapf, NULL);

	return 0;
}