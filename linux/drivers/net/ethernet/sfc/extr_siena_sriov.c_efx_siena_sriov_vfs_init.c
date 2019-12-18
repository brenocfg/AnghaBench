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
typedef  unsigned int u16 ;
struct siena_vf {unsigned int buftbl_base; unsigned int pci_rid; int /*<<< orphan*/  buf; int /*<<< orphan*/  pci_name; } ;
struct siena_nic_data {unsigned int vf_buftbl_base; struct siena_vf* vf; } ;
struct pci_dev {unsigned int devfn; TYPE_1__* bus; } ;
struct efx_nic {unsigned int vf_count; struct siena_nic_data* nic_data; struct pci_dev* pci_dev; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_PAGE_SIZE ; 
 unsigned int EFX_VF_BUFTBL_PER_VI ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 scalar_t__ PCI_SRIOV_VF_OFFSET ; 
 scalar_t__ PCI_SRIOV_VF_STRIDE ; 
 int efx_nic_alloc_buffer (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_siena_sriov_vfs_fini (struct efx_nic*) ; 
 unsigned int efx_vf_size (struct efx_nic*) ; 
 int pci_domain_nr (TYPE_1__*) ; 
 unsigned int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int) ; 

__attribute__((used)) static int efx_siena_sriov_vfs_init(struct efx_nic *efx)
{
	struct pci_dev *pci_dev = efx->pci_dev;
	struct siena_nic_data *nic_data = efx->nic_data;
	unsigned index, devfn, sriov, buftbl_base;
	u16 offset, stride;
	struct siena_vf *vf;
	int rc;

	sriov = pci_find_ext_capability(pci_dev, PCI_EXT_CAP_ID_SRIOV);
	if (!sriov)
		return -ENOENT;

	pci_read_config_word(pci_dev, sriov + PCI_SRIOV_VF_OFFSET, &offset);
	pci_read_config_word(pci_dev, sriov + PCI_SRIOV_VF_STRIDE, &stride);

	buftbl_base = nic_data->vf_buftbl_base;
	devfn = pci_dev->devfn + offset;
	for (index = 0; index < efx->vf_count; ++index) {
		vf = nic_data->vf + index;

		/* Reserve buffer entries */
		vf->buftbl_base = buftbl_base;
		buftbl_base += EFX_VF_BUFTBL_PER_VI * efx_vf_size(efx);

		vf->pci_rid = devfn;
		snprintf(vf->pci_name, sizeof(vf->pci_name),
			 "%04x:%02x:%02x.%d",
			 pci_domain_nr(pci_dev->bus), pci_dev->bus->number,
			 PCI_SLOT(devfn), PCI_FUNC(devfn));

		rc = efx_nic_alloc_buffer(efx, &vf->buf, EFX_PAGE_SIZE,
					  GFP_KERNEL);
		if (rc)
			goto fail;

		devfn += stride;
	}

	return 0;

fail:
	efx_siena_sriov_vfs_fini(efx);
	return rc;
}