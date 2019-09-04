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
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,unsigned int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,unsigned short) ; 

void PCIwrite(byte bus, byte func, int offset, void *data, int length,
	      void *pci_dev_handle)
{
	struct pci_dev *dev = (struct pci_dev *) pci_dev_handle;

	switch (length) {
	case 1:		/* byte */
		pci_write_config_byte(dev, offset,
				      *(unsigned char *) data);
		break;
	case 2:		/* word */
		pci_write_config_word(dev, offset,
				      *(unsigned short *) data);
		break;
	case 4:		/* dword */
		pci_write_config_dword(dev, offset,
				       *(unsigned int *) data);
		break;

	default:		/* buffer */
		if (!(length % 4) && !(length & 0x03)) {	/* Copy as dword */
			dword *p = (dword *) data;
			length /= 4;

			while (length--) {
				pci_write_config_dword(dev, offset,
						       *(unsigned int *)
						       p++);
			}
		} else {	/* copy as byte stream */
			byte *p = (byte *) data;

			while (length--) {
				pci_write_config_byte(dev, offset,
						      *(unsigned char *)
						      p++);
			}
		}
	}
}