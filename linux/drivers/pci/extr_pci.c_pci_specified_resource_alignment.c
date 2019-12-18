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
struct pci_dev {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_PROBE_ONLY ; 
 int pci_dev_str_match (struct pci_dev*,char const*,char const**) ; 
 scalar_t__ pci_has_flag (int /*<<< orphan*/ ) ; 
 int pcibios_default_alignment () ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  pr_info_once (char*) ; 
 int /*<<< orphan*/  resource_alignment_lock ; 
 char* resource_alignment_param ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int*,int*) ; 

__attribute__((used)) static resource_size_t pci_specified_resource_alignment(struct pci_dev *dev,
							bool *resize)
{
	int align_order, count;
	resource_size_t align = pcibios_default_alignment();
	const char *p;
	int ret;

	spin_lock(&resource_alignment_lock);
	p = resource_alignment_param;
	if (!p || !*p)
		goto out;
	if (pci_has_flag(PCI_PROBE_ONLY)) {
		align = 0;
		pr_info_once("PCI: Ignoring requested alignments (PCI_PROBE_ONLY)\n");
		goto out;
	}

	while (*p) {
		count = 0;
		if (sscanf(p, "%d%n", &align_order, &count) == 1 &&
							p[count] == '@') {
			p += count + 1;
		} else {
			align_order = -1;
		}

		ret = pci_dev_str_match(dev, p, &p);
		if (ret == 1) {
			*resize = true;
			if (align_order == -1)
				align = PAGE_SIZE;
			else
				align = 1 << align_order;
			break;
		} else if (ret < 0) {
			pr_err("PCI: Can't parse resource_alignment parameter: %s\n",
			       p);
			break;
		}

		if (*p != ';' && *p != ',') {
			/* End of param or invalid format */
			break;
		}
		p++;
	}
out:
	spin_unlock(&resource_alignment_lock);
	return align;
}