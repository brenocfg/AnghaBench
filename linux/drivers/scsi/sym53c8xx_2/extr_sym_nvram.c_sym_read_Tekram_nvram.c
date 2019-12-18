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
typedef  int u_short ;
typedef  int u_char ;
struct sym_device {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  Tekram_nvram ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_NCR_53C875 131 
#define  PCI_DEVICE_ID_NCR_53C885 130 
#define  PCI_DEVICE_ID_NCR_53C895 129 
#define  PCI_DEVICE_ID_NCR_53C896 128 
 int /*<<< orphan*/  TEKRAM_24C16_NVRAM_ADDRESS ; 
 int sym_read_S24C16_nvram (struct sym_device*,int /*<<< orphan*/ ,int*,int) ; 
 int sym_read_T93C46_nvram (struct sym_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sym_read_Tekram_nvram (struct sym_device *np, Tekram_nvram *nvram)
{
	u_char *data = (u_char *) nvram;
	int len = sizeof(*nvram);
	u_short	csum;
	int x;

	switch (np->pdev->device) {
	case PCI_DEVICE_ID_NCR_53C885:
	case PCI_DEVICE_ID_NCR_53C895:
	case PCI_DEVICE_ID_NCR_53C896:
		x = sym_read_S24C16_nvram(np, TEKRAM_24C16_NVRAM_ADDRESS,
					  data, len);
		break;
	case PCI_DEVICE_ID_NCR_53C875:
		x = sym_read_S24C16_nvram(np, TEKRAM_24C16_NVRAM_ADDRESS,
					  data, len);
		if (!x)
			break;
		/* fall through */
	default:
		x = sym_read_T93C46_nvram(np, nvram);
		break;
	}
	if (x)
		return 1;

	/* verify checksum */
	for (x = 0, csum = 0; x < len - 1; x += 2)
		csum += data[x] + (data[x+1] << 8);
	if (csum != 0x1234)
		return 1;

	return 0;
}