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
typedef  int u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
#define  MPI_MANUFACTPAGE_DEVICEID_FC909 142 
#define  MPI_MANUFACTPAGE_DEVICEID_FC919 141 
#define  MPI_MANUFACTPAGE_DEVICEID_FC919X 140 
#define  MPI_MANUFACTPAGE_DEVICEID_FC929 139 
#define  MPI_MANUFACTPAGE_DEVICEID_FC929X 138 
#define  MPI_MANUFACTPAGE_DEVICEID_FC939X 137 
#define  MPI_MANUFACTPAGE_DEVICEID_FC949E 136 
#define  MPI_MANUFACTPAGE_DEVICEID_FC949X 135 
#define  MPI_MANUFACTPAGE_DEVID_1030_53C1035 134 
#define  MPI_MANUFACTPAGE_DEVID_53C1030 133 
#define  MPI_MANUFACTPAGE_DEVID_SAS1064 132 
#define  MPI_MANUFACTPAGE_DEVID_SAS1064E 131 
#define  MPI_MANUFACTPAGE_DEVID_SAS1068 130 
#define  MPI_MANUFACTPAGE_DEVID_SAS1068E 129 
#define  MPI_MANUFACTPAGE_DEVID_SAS1078 128 
 scalar_t__ PCI_VENDOR_ID_BROCADE ; 

__attribute__((used)) static const char*
mpt_get_product_name(u16 vendor, u16 device, u8 revision)
{
	char *product_str = NULL;

	if (vendor == PCI_VENDOR_ID_BROCADE) {
		switch (device)
		{
		case MPI_MANUFACTPAGE_DEVICEID_FC949E:
			switch (revision)
			{
			case 0x00:
				product_str = "BRE040 A0";
				break;
			case 0x01:
				product_str = "BRE040 A1";
				break;
			default:
				product_str = "BRE040";
				break;
			}
			break;
		}
		goto out;
	}

	switch (device)
	{
	case MPI_MANUFACTPAGE_DEVICEID_FC909:
		product_str = "LSIFC909 B1";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC919:
		product_str = "LSIFC919 B0";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC929:
		product_str = "LSIFC929 B0";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC919X:
		if (revision < 0x80)
			product_str = "LSIFC919X A0";
		else
			product_str = "LSIFC919XL A1";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC929X:
		if (revision < 0x80)
			product_str = "LSIFC929X A0";
		else
			product_str = "LSIFC929XL A1";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC939X:
		product_str = "LSIFC939X A1";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC949X:
		product_str = "LSIFC949X A1";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC949E:
		switch (revision)
		{
		case 0x00:
			product_str = "LSIFC949E A0";
			break;
		case 0x01:
			product_str = "LSIFC949E A1";
			break;
		default:
			product_str = "LSIFC949E";
			break;
		}
		break;
	case MPI_MANUFACTPAGE_DEVID_53C1030:
		switch (revision)
		{
		case 0x00:
			product_str = "LSI53C1030 A0";
			break;
		case 0x01:
			product_str = "LSI53C1030 B0";
			break;
		case 0x03:
			product_str = "LSI53C1030 B1";
			break;
		case 0x07:
			product_str = "LSI53C1030 B2";
			break;
		case 0x08:
			product_str = "LSI53C1030 C0";
			break;
		case 0x80:
			product_str = "LSI53C1030T A0";
			break;
		case 0x83:
			product_str = "LSI53C1030T A2";
			break;
		case 0x87:
			product_str = "LSI53C1030T A3";
			break;
		case 0xc1:
			product_str = "LSI53C1020A A1";
			break;
		default:
			product_str = "LSI53C1030";
			break;
		}
		break;
	case MPI_MANUFACTPAGE_DEVID_1030_53C1035:
		switch (revision)
		{
		case 0x03:
			product_str = "LSI53C1035 A2";
			break;
		case 0x04:
			product_str = "LSI53C1035 B0";
			break;
		default:
			product_str = "LSI53C1035";
			break;
		}
		break;
	case MPI_MANUFACTPAGE_DEVID_SAS1064:
		switch (revision)
		{
		case 0x00:
			product_str = "LSISAS1064 A1";
			break;
		case 0x01:
			product_str = "LSISAS1064 A2";
			break;
		case 0x02:
			product_str = "LSISAS1064 A3";
			break;
		case 0x03:
			product_str = "LSISAS1064 A4";
			break;
		default:
			product_str = "LSISAS1064";
			break;
		}
		break;
	case MPI_MANUFACTPAGE_DEVID_SAS1064E:
		switch (revision)
		{
		case 0x00:
			product_str = "LSISAS1064E A0";
			break;
		case 0x01:
			product_str = "LSISAS1064E B0";
			break;
		case 0x02:
			product_str = "LSISAS1064E B1";
			break;
		case 0x04:
			product_str = "LSISAS1064E B2";
			break;
		case 0x08:
			product_str = "LSISAS1064E B3";
			break;
		default:
			product_str = "LSISAS1064E";
			break;
		}
		break;
	case MPI_MANUFACTPAGE_DEVID_SAS1068:
		switch (revision)
		{
		case 0x00:
			product_str = "LSISAS1068 A0";
			break;
		case 0x01:
			product_str = "LSISAS1068 B0";
			break;
		case 0x02:
			product_str = "LSISAS1068 B1";
			break;
		default:
			product_str = "LSISAS1068";
			break;
		}
		break;
	case MPI_MANUFACTPAGE_DEVID_SAS1068E:
		switch (revision)
		{
		case 0x00:
			product_str = "LSISAS1068E A0";
			break;
		case 0x01:
			product_str = "LSISAS1068E B0";
			break;
		case 0x02:
			product_str = "LSISAS1068E B1";
			break;
		case 0x04:
			product_str = "LSISAS1068E B2";
			break;
		case 0x08:
			product_str = "LSISAS1068E B3";
			break;
		default:
			product_str = "LSISAS1068E";
			break;
		}
		break;
	case MPI_MANUFACTPAGE_DEVID_SAS1078:
		switch (revision)
		{
		case 0x00:
			product_str = "LSISAS1078 A0";
			break;
		case 0x01:
			product_str = "LSISAS1078 B0";
			break;
		case 0x02:
			product_str = "LSISAS1078 C0";
			break;
		case 0x03:
			product_str = "LSISAS1078 C1";
			break;
		case 0x04:
			product_str = "LSISAS1078 C2";
			break;
		default:
			product_str = "LSISAS1078";
			break;
		}
		break;
	}

 out:
	return product_str;
}