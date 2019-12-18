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
struct vnt_private {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_free_info (struct vnt_private*) ; 
 struct vnt_private* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void vt6655_remove(struct pci_dev *pcid)
{
	struct vnt_private *priv = pci_get_drvdata(pcid);

	if (!priv)
		return;
	device_free_info(priv);
}