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
struct vfio_pci_device {scalar_t__ vconfig; int /*<<< orphan*/  pdev; } ;
struct perm_bits {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_FLAGS ; 
 int PCI_CAP_LIST_ID ; 
 int PCI_CAP_LIST_NEXT ; 
 int PCI_CFG_SPACE_SIZE ; 
 int PCI_STD_HEADER_SIZEOF ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int vfio_user_config_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vfio_direct_config_read(struct vfio_pci_device *vdev, int pos,
				   int count, struct perm_bits *perm,
				   int offset, __le32 *val)
{
	int ret;

	ret = vfio_user_config_read(vdev->pdev, pos, val, count);
	if (ret)
		return ret;

	if (pos >= PCI_CFG_SPACE_SIZE) { /* Extended cap header mangling */
		if (offset < 4)
			memcpy(val, vdev->vconfig + pos, count);
	} else if (pos >= PCI_STD_HEADER_SIZEOF) { /* Std cap mangling */
		if (offset == PCI_CAP_LIST_ID && count > 1)
			memcpy(val, vdev->vconfig + pos,
			       min(PCI_CAP_FLAGS, count));
		else if (offset == PCI_CAP_LIST_NEXT)
			memcpy(val, vdev->vconfig + pos, 1);
	}

	return count;
}