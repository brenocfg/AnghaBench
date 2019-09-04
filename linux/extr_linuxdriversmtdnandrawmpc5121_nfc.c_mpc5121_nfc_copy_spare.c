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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int dummy; } ;
struct mtd_info {int oobsize; int writesize; } ;
struct mpc5121_nfc_prv {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ NFC_SPARE_AREA (int) ; 
 int NFC_SPARE_BUFFERS ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void mpc5121_nfc_copy_spare(struct mtd_info *mtd, uint offset,
						u8 *buffer, uint size, int wr)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(nand);
	uint o, s, sbsize, blksize;

	/*
	 * NAND spare area is available through NFC spare buffers.
	 * The NFC divides spare area into (page_size / 512) chunks.
	 * Each chunk is placed into separate spare memory area, using
	 * first (spare_size / num_of_chunks) bytes of the buffer.
	 *
	 * For NAND device in which the spare area is not divided fully
	 * by the number of chunks, number of used bytes in each spare
	 * buffer is rounded down to the nearest even number of bytes,
	 * and all remaining bytes are added to the last used spare area.
	 *
	 * For more information read section 26.6.10 of MPC5121e
	 * Microcontroller Reference Manual, Rev. 3.
	 */

	/* Calculate number of valid bytes in each spare buffer */
	sbsize = (mtd->oobsize / (mtd->writesize / 512)) & ~1;

	while (size) {
		/* Calculate spare buffer number */
		s = offset / sbsize;
		if (s > NFC_SPARE_BUFFERS - 1)
			s = NFC_SPARE_BUFFERS - 1;

		/*
		 * Calculate offset to requested data block in selected spare
		 * buffer and its size.
		 */
		o = offset - (s * sbsize);
		blksize = min(sbsize - o, size);

		if (wr)
			memcpy_toio(prv->regs + NFC_SPARE_AREA(s) + o,
							buffer, blksize);
		else
			memcpy_fromio(buffer,
				prv->regs + NFC_SPARE_AREA(s) + o, blksize);

		buffer += blksize;
		offset += blksize;
		size -= blksize;
	};
}