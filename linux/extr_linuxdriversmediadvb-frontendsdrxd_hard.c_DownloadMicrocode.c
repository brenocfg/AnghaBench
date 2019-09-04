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
typedef  int u32 ;
typedef  int u16 ;
struct drxd_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRX_I2C_CLEARCRC ; 
 int WriteBlock (struct drxd_state*,int,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DownloadMicrocode(struct drxd_state *state,
			     const u8 *pMCImage, u32 Length)
{
	u8 *pSrc;
	u32 Address;
	u16 nBlocks;
	u16 BlockSize;
	u32 offset = 0;
	int i, status = 0;

	pSrc = (u8 *) pMCImage;
	/* We're not using Flags */
	/* Flags = (pSrc[0] << 8) | pSrc[1]; */
	pSrc += sizeof(u16);
	offset += sizeof(u16);
	nBlocks = (pSrc[0] << 8) | pSrc[1];
	pSrc += sizeof(u16);
	offset += sizeof(u16);

	for (i = 0; i < nBlocks; i++) {
		Address = (pSrc[0] << 24) | (pSrc[1] << 16) |
		    (pSrc[2] << 8) | pSrc[3];
		pSrc += sizeof(u32);
		offset += sizeof(u32);

		BlockSize = ((pSrc[0] << 8) | pSrc[1]) * sizeof(u16);
		pSrc += sizeof(u16);
		offset += sizeof(u16);

		/* We're not using Flags */
		/* u16 Flags = (pSrc[0] << 8) | pSrc[1]; */
		pSrc += sizeof(u16);
		offset += sizeof(u16);

		/* We're not using BlockCRC */
		/* u16 BlockCRC = (pSrc[0] << 8) | pSrc[1]; */
		pSrc += sizeof(u16);
		offset += sizeof(u16);

		status = WriteBlock(state, Address, BlockSize,
				    pSrc, DRX_I2C_CLEARCRC);
		if (status < 0)
			break;
		pSrc += BlockSize;
		offset += BlockSize;
	}

	return status;
}