#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct us_data {scalar_t__ extra; } ;
struct ms_lib_type_extdat {int dummy; } ;
struct ms_bootblock_sysinf {scalar_t__ bMsClass; int wPageSize; int bSecuritySupport; scalar_t__ bReserved1; scalar_t__ bReserved2; scalar_t__ bFormatType; scalar_t__ bUsage; int wBlockSize; int wBlockNumber; int wTotalBlockNumber; int wMemorySize; int /*<<< orphan*/  bCardType; } ;
struct ms_bootblock_sysent {TYPE_1__* entry; } ;
struct ms_bootblock_page0 {struct ms_bootblock_sysent sysent; struct ms_bootblock_sysinf sysinf; } ;
struct ms_bootblock_idi {int /*<<< orphan*/  wIDIbytesPerSector; int /*<<< orphan*/  wIDIgeneralConfiguration; } ;
struct TYPE_5__ {struct ms_bootblock_idi idi; } ;
struct ms_bootblock_cis_idi {TYPE_2__ idi; } ;
struct TYPE_6__ {int blockSize; int NumberOfPhyBlock; int PagesPerBlock; int NumberOfSegment; int BytesPerSector; scalar_t__ NumberOfLogBlock; int /*<<< orphan*/  cardType; } ;
struct ene_ub6250_info {TYPE_3__ MS_Lib; scalar_t__ MS_Model; } ;
struct TYPE_4__ {scalar_t__ bType; int /*<<< orphan*/  dwSize; int /*<<< orphan*/  dwStart; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MS_BYTES_PER_PAGE ; 
#define  MS_ERROR_FLASH_READ 134 
 scalar_t__ MS_IDI_GENERAL_CONF ; 
 int /*<<< orphan*/  MS_LIB_CTRL_RDONLY ; 
 int MS_NUMBER_OF_SYSTEM_ENTRY ; 
 int MS_PHYSICAL_BLOCKS_PER_SEGMENT ; 
#define  MS_STATUS_ERROR 133 
#define  MS_STATUS_SUCCESS 132 
#define  MS_STATUS_WRITE_PROTECT 131 
 scalar_t__ MS_SYSENT_TYPE_CIS_IDI ; 
 scalar_t__ MS_SYSENT_TYPE_INVALID_BLOCK ; 
#define  MS_SYSINF_CARDTYPE_HYBRID 130 
#define  MS_SYSINF_CARDTYPE_RDONLY 129 
#define  MS_SYSINF_CARDTYPE_RDWR 128 
 scalar_t__ MS_SYSINF_FORMAT_FAT ; 
 scalar_t__ MS_SYSINF_MSCLASS_TYPE_1 ; 
 scalar_t__ MS_SYSINF_PAGE_SIZE ; 
 scalar_t__ MS_SYSINF_RESERVED1 ; 
 scalar_t__ MS_SYSINF_RESERVED2 ; 
 int MS_SYSINF_SECURITY ; 
 int MS_SYSINF_SECURITY_SUPPORT ; 
 scalar_t__ MS_SYSINF_USAGE_GENERAL ; 
 int SIZE_OF_KIRO ; 
 scalar_t__ be16_to_cpu (int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ms_lib_alloc_logicalmap (struct us_data*) ; 
 int /*<<< orphan*/  ms_lib_ctrl_reset (struct ene_ub6250_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_lib_ctrl_set (struct ene_ub6250_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_lib_free_logicalmap (struct us_data*) ; 
 int /*<<< orphan*/  ms_lib_set_bootblockmark (struct us_data*,int) ; 
 int /*<<< orphan*/  ms_lib_set_initialerrorblock (struct us_data*,int) ; 
 int ms_read_readpage (struct us_data*,int,scalar_t__,int*,struct ms_lib_type_extdat*) ; 

__attribute__((used)) static int ms_lib_process_bootblock(struct us_data *us, u16 PhyBlock, u8 *PageData)
{
	struct ms_bootblock_sysent *SysEntry;
	struct ms_bootblock_sysinf *SysInfo;
	u32 i, result;
	u8 PageNumber;
	u8 *PageBuffer;
	struct ms_lib_type_extdat ExtraData;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	PageBuffer = kmalloc(MS_BYTES_PER_PAGE, GFP_KERNEL);
	if (PageBuffer == NULL)
		return (u32)-1;

	result = (u32)-1;

	SysInfo = &(((struct ms_bootblock_page0 *)PageData)->sysinf);

	if ((SysInfo->bMsClass != MS_SYSINF_MSCLASS_TYPE_1) ||
		(be16_to_cpu(SysInfo->wPageSize) != MS_SYSINF_PAGE_SIZE) ||
		((SysInfo->bSecuritySupport & MS_SYSINF_SECURITY) == MS_SYSINF_SECURITY_SUPPORT) ||
		(SysInfo->bReserved1 != MS_SYSINF_RESERVED1) ||
		(SysInfo->bReserved2 != MS_SYSINF_RESERVED2) ||
		(SysInfo->bFormatType != MS_SYSINF_FORMAT_FAT) ||
		(SysInfo->bUsage != MS_SYSINF_USAGE_GENERAL))
		goto exit;
		/* */
	switch (info->MS_Lib.cardType = SysInfo->bCardType) {
	case MS_SYSINF_CARDTYPE_RDONLY:
		ms_lib_ctrl_set(info, MS_LIB_CTRL_RDONLY);
		break;
	case MS_SYSINF_CARDTYPE_RDWR:
		ms_lib_ctrl_reset(info, MS_LIB_CTRL_RDONLY);
		break;
	case MS_SYSINF_CARDTYPE_HYBRID:
	default:
		goto exit;
	}

	info->MS_Lib.blockSize = be16_to_cpu(SysInfo->wBlockSize);
	info->MS_Lib.NumberOfPhyBlock = be16_to_cpu(SysInfo->wBlockNumber);
	info->MS_Lib.NumberOfLogBlock = be16_to_cpu(SysInfo->wTotalBlockNumber)-2;
	info->MS_Lib.PagesPerBlock = info->MS_Lib.blockSize * SIZE_OF_KIRO / MS_BYTES_PER_PAGE;
	info->MS_Lib.NumberOfSegment = info->MS_Lib.NumberOfPhyBlock / MS_PHYSICAL_BLOCKS_PER_SEGMENT;
	info->MS_Model = be16_to_cpu(SysInfo->wMemorySize);

	/*Allocate to all number of logicalblock and physicalblock */
	if (ms_lib_alloc_logicalmap(us))
		goto exit;

	/* Mark the book block */
	ms_lib_set_bootblockmark(us, PhyBlock);

	SysEntry = &(((struct ms_bootblock_page0 *)PageData)->sysent);

	for (i = 0; i < MS_NUMBER_OF_SYSTEM_ENTRY; i++) {
		u32  EntryOffset, EntrySize;

		EntryOffset = be32_to_cpu(SysEntry->entry[i].dwStart);

		if (EntryOffset == 0xffffff)
			continue;
		EntrySize = be32_to_cpu(SysEntry->entry[i].dwSize);

		if (EntrySize == 0)
			continue;

		if (EntryOffset + MS_BYTES_PER_PAGE + EntrySize > info->MS_Lib.blockSize * (u32)SIZE_OF_KIRO)
			continue;

		if (i == 0) {
			u8 PrevPageNumber = 0;
			u16 phyblk;

			if (SysEntry->entry[i].bType != MS_SYSENT_TYPE_INVALID_BLOCK)
				goto exit;

			while (EntrySize > 0) {

				PageNumber = (u8)(EntryOffset / MS_BYTES_PER_PAGE + 1);
				if (PageNumber != PrevPageNumber) {
					switch (ms_read_readpage(us, PhyBlock, PageNumber, (u32 *)PageBuffer, &ExtraData)) {
					case MS_STATUS_SUCCESS:
						break;
					case MS_STATUS_WRITE_PROTECT:
					case MS_ERROR_FLASH_READ:
					case MS_STATUS_ERROR:
					default:
						goto exit;
					}

					PrevPageNumber = PageNumber;
				}

				phyblk = be16_to_cpu(*(u16 *)(PageBuffer + (EntryOffset % MS_BYTES_PER_PAGE)));
				if (phyblk < 0x0fff)
					ms_lib_set_initialerrorblock(us, phyblk);

				EntryOffset += 2;
				EntrySize -= 2;
			}
		} else if (i == 1) {  /* CIS/IDI */
			struct ms_bootblock_idi *idi;

			if (SysEntry->entry[i].bType != MS_SYSENT_TYPE_CIS_IDI)
				goto exit;

			switch (ms_read_readpage(us, PhyBlock, (u8)(EntryOffset / MS_BYTES_PER_PAGE + 1), (u32 *)PageBuffer, &ExtraData)) {
			case MS_STATUS_SUCCESS:
				break;
			case MS_STATUS_WRITE_PROTECT:
			case MS_ERROR_FLASH_READ:
			case MS_STATUS_ERROR:
			default:
				goto exit;
			}

			idi = &((struct ms_bootblock_cis_idi *)(PageBuffer + (EntryOffset % MS_BYTES_PER_PAGE)))->idi.idi;
			if (le16_to_cpu(idi->wIDIgeneralConfiguration) != MS_IDI_GENERAL_CONF)
				goto exit;

			info->MS_Lib.BytesPerSector = le16_to_cpu(idi->wIDIbytesPerSector);
			if (info->MS_Lib.BytesPerSector != MS_BYTES_PER_PAGE)
				goto exit;
		}
	} /* End for .. */

	result = 0;

exit:
	if (result)
		ms_lib_free_logicalmap(us);

	kfree(PageBuffer);

	result = 0;
	return result;
}