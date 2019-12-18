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
typedef  int ushort ;
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  uchar ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_MCODE_CHKSUM_W ; 
 int /*<<< orphan*/  ASCV_MCODE_SIZE_W ; 
 scalar_t__ ASC_CODE_SEC_BEG ; 
 int /*<<< orphan*/  ASC_DBG (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ AscMemSumLramWord (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrToLram (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  AscMemWordSetLram (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
AscLoadMicroCode(PortAddr iop_base, ushort s_addr,
		 const uchar *mcode_buf, ushort mcode_size)
{
	u32 chksum;
	ushort mcode_word_size;
	ushort mcode_chksum;

	/* Write the microcode buffer starting at LRAM address 0. */
	mcode_word_size = (ushort)(mcode_size >> 1);
	AscMemWordSetLram(iop_base, s_addr, 0, mcode_word_size);
	AscMemWordCopyPtrToLram(iop_base, s_addr, mcode_buf, mcode_word_size);

	chksum = AscMemSumLramWord(iop_base, s_addr, mcode_word_size);
	ASC_DBG(1, "chksum 0x%lx\n", (ulong)chksum);
	mcode_chksum = (ushort)AscMemSumLramWord(iop_base,
						 (ushort)ASC_CODE_SEC_BEG,
						 (ushort)((mcode_size -
							   s_addr - (ushort)
							   ASC_CODE_SEC_BEG) /
							  2));
	ASC_DBG(1, "mcode_chksum 0x%lx\n", (ulong)mcode_chksum);
	AscWriteLramWord(iop_base, ASCV_MCODE_CHKSUM_W, mcode_chksum);
	AscWriteLramWord(iop_base, ASCV_MCODE_SIZE_W, mcode_size);
	return chksum;
}