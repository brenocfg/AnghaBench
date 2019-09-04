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
typedef  int u32 ;
struct pci_osc_bit_struct {int bit; int /*<<< orphan*/  desc; } ;
struct acpi_pci_root {TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,char*) ; 
 scalar_t__ snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_osc_bits(struct acpi_pci_root *root, char *msg, u32 word,
			    struct pci_osc_bit_struct *table, int size)
{
	char buf[80];
	int i, len = 0;
	struct pci_osc_bit_struct *entry;

	buf[0] = '\0';
	for (i = 0, entry = table; i < size; i++, entry++)
		if (word & entry->bit)
			len += snprintf(buf + len, sizeof(buf) - len, "%s%s",
					len ? " " : "", entry->desc);

	dev_info(&root->device->dev, "_OSC: %s [%s]\n", msg, buf);
}