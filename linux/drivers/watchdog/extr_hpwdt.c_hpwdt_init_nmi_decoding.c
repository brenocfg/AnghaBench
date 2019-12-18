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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NMI_IO_CHECK ; 
 int /*<<< orphan*/  NMI_SERR ; 
 int /*<<< orphan*/  NMI_UNKNOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hpwdt_pretimeout ; 
 int register_nmi_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unregister_nmi_handler (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hpwdt_init_nmi_decoding(struct pci_dev *dev)
{
#ifdef CONFIG_HPWDT_NMI_DECODING
	int retval;
	/*
	 * Only one function can register for NMI_UNKNOWN
	 */
	retval = register_nmi_handler(NMI_UNKNOWN, hpwdt_pretimeout, 0, "hpwdt");
	if (retval)
		goto error;
	retval = register_nmi_handler(NMI_SERR, hpwdt_pretimeout, 0, "hpwdt");
	if (retval)
		goto error1;
	retval = register_nmi_handler(NMI_IO_CHECK, hpwdt_pretimeout, 0, "hpwdt");
	if (retval)
		goto error2;

	dev_info(&dev->dev,
		"HPE Watchdog Timer Driver: NMI decoding initialized\n");

	return 0;

error2:
	unregister_nmi_handler(NMI_SERR, "hpwdt");
error1:
	unregister_nmi_handler(NMI_UNKNOWN, "hpwdt");
error:
	dev_warn(&dev->dev,
		"Unable to register a die notifier (err=%d).\n",
		retval);
	return retval;
#endif	/* CONFIG_HPWDT_NMI_DECODING */
	return 0;
}