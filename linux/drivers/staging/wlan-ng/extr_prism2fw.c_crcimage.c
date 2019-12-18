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
struct s3crcrec {int addr; int /*<<< orphan*/  len; int /*<<< orphan*/  dowrite; } ;
struct imgchunk {int addr; int len; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crcimage(struct imgchunk *fchunk, unsigned int nfchunks,
		    struct s3crcrec *s3crc, unsigned int ns3crc)
{
	int result = 0;
	int i;
	int c;
	u32 crcstart;
	u32 cstart = 0;
	u32 cend;
	u8 *dest;
	u32 chunkoff;

	for (i = 0; i < ns3crc; i++) {
		if (!s3crc[i].dowrite)
			continue;
		crcstart = s3crc[i].addr;
		/* Find chunk */
		for (c = 0; c < nfchunks; c++) {
			cstart = fchunk[c].addr;
			cend = fchunk[c].addr + fchunk[c].len;
			/* the line below does an address & len match search */
			/* unfortunately, I've found that the len fields of */
			/* some crc records don't match with the length of */
			/* the actual data, so we're not checking right now */
			/* if (crcstart-2 >= cstart && crcend <= cend) break; */

			/* note the -2 below, it's to make sure the chunk has */
			/* space for the CRC value */
			if (crcstart - 2 >= cstart && crcstart < cend)
				break;
		}
		if (c >= nfchunks) {
			pr_err("Failed to find chunk for crcrec[%d], addr=0x%06x len=%d , aborting crc.\n",
			       i, s3crc[i].addr, s3crc[i].len);
			return 1;
		}

		/* Insert crc */
		pr_debug("Adding crc @ 0x%06x\n", s3crc[i].addr - 2);
		chunkoff = crcstart - cstart - 2;
		dest = fchunk[c].data + chunkoff;
		*dest = 0xde;
		*(dest + 1) = 0xc0;
	}
	return result;
}