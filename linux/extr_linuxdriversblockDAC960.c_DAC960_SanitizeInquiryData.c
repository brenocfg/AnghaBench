#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int PeripheralDeviceType; unsigned char* VendorIdentification; unsigned char* ProductIdentification; unsigned char* ProductRevisionLevel; } ;
struct TYPE_5__ {int PeripheralDeviceType; int PageLength; unsigned char* ProductSerialNumber; } ;
typedef  TYPE_1__ DAC960_SCSI_Inquiry_UnitSerialNumber_T ;
typedef  TYPE_2__ DAC960_SCSI_Inquiry_T ;

/* Variables and functions */

__attribute__((used)) static void DAC960_SanitizeInquiryData(DAC960_SCSI_Inquiry_T
					 *InquiryStandardData,
				       DAC960_SCSI_Inquiry_UnitSerialNumber_T
					 *InquiryUnitSerialNumber,
				       unsigned char *Vendor,
				       unsigned char *Model,
				       unsigned char *Revision,
				       unsigned char *SerialNumber)
{
  int SerialNumberLength, i;
  if (InquiryStandardData->PeripheralDeviceType == 0x1F) return;
  for (i = 0; i < sizeof(InquiryStandardData->VendorIdentification); i++)
    {
      unsigned char VendorCharacter =
	InquiryStandardData->VendorIdentification[i];
      Vendor[i] = (VendorCharacter >= ' ' && VendorCharacter <= '~'
		   ? VendorCharacter : ' ');
    }
  Vendor[sizeof(InquiryStandardData->VendorIdentification)] = '\0';
  for (i = 0; i < sizeof(InquiryStandardData->ProductIdentification); i++)
    {
      unsigned char ModelCharacter =
	InquiryStandardData->ProductIdentification[i];
      Model[i] = (ModelCharacter >= ' ' && ModelCharacter <= '~'
		  ? ModelCharacter : ' ');
    }
  Model[sizeof(InquiryStandardData->ProductIdentification)] = '\0';
  for (i = 0; i < sizeof(InquiryStandardData->ProductRevisionLevel); i++)
    {
      unsigned char RevisionCharacter =
	InquiryStandardData->ProductRevisionLevel[i];
      Revision[i] = (RevisionCharacter >= ' ' && RevisionCharacter <= '~'
		     ? RevisionCharacter : ' ');
    }
  Revision[sizeof(InquiryStandardData->ProductRevisionLevel)] = '\0';
  if (InquiryUnitSerialNumber->PeripheralDeviceType == 0x1F) return;
  SerialNumberLength = InquiryUnitSerialNumber->PageLength;
  if (SerialNumberLength >
      sizeof(InquiryUnitSerialNumber->ProductSerialNumber))
    SerialNumberLength = sizeof(InquiryUnitSerialNumber->ProductSerialNumber);
  for (i = 0; i < SerialNumberLength; i++)
    {
      unsigned char SerialNumberCharacter =
	InquiryUnitSerialNumber->ProductSerialNumber[i];
      SerialNumber[i] =
	(SerialNumberCharacter >= ' ' && SerialNumberCharacter <= '~'
	 ? SerialNumberCharacter : ' ');
    }
  SerialNumber[SerialNumberLength] = '\0';
}