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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int PCI_ACS_CR ; 
 scalar_t__ PCI_ACS_CTRL ; 
 int PCI_ACS_EC ; 
 int PCI_ACS_RR ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ACS ; 
 char* disable_acs_redir_param ; 
 int /*<<< orphan*/  pci_dev_specific_disable_acs_redir (struct pci_dev*) ; 
 int pci_dev_str_match (struct pci_dev*,char const*,char const**) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_info_once (char*,char*) ; 

__attribute__((used)) static void pci_disable_acs_redir(struct pci_dev *dev)
{
	int ret = 0;
	const char *p;
	int pos;
	u16 ctrl;

	if (!disable_acs_redir_param)
		return;

	p = disable_acs_redir_param;
	while (*p) {
		ret = pci_dev_str_match(dev, p, &p);
		if (ret < 0) {
			pr_info_once("PCI: Can't parse disable_acs_redir parameter: %s\n",
				     disable_acs_redir_param);

			break;
		} else if (ret == 1) {
			/* Found a match */
			break;
		}

		if (*p != ';' && *p != ',') {
			/* End of param or invalid format */
			break;
		}
		p++;
	}

	if (ret != 1)
		return;

	if (!pci_dev_specific_disable_acs_redir(dev))
		return;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ACS);
	if (!pos) {
		pci_warn(dev, "cannot disable ACS redirect for this hardware as it does not have ACS capabilities\n");
		return;
	}

	pci_read_config_word(dev, pos + PCI_ACS_CTRL, &ctrl);

	/* P2P Request & Completion Redirect */
	ctrl &= ~(PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_EC);

	pci_write_config_word(dev, pos + PCI_ACS_CTRL, ctrl);

	pci_info(dev, "disabled ACS redirect\n");
}