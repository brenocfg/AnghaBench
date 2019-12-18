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
typedef  size_t u32 ;
struct hantro_dev {int dummy; } ;

/* Variables and functions */
 size_t H1_JPEG_QUANT_TABLE_COUNT ; 
 int /*<<< orphan*/  H1_REG_JPEG_CHROMA_QUAT (size_t) ; 
 int /*<<< orphan*/  H1_REG_JPEG_LUMA_QUAT (size_t) ; 
 size_t get_unaligned_be32 (unsigned char*) ; 
 int /*<<< orphan*/  vepu_write_relaxed (struct hantro_dev*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hantro_h1_jpeg_enc_set_qtable(struct hantro_dev *vpu,
			      unsigned char *luma_qtable,
			      unsigned char *chroma_qtable)
{
	u32 reg, i;

	for (i = 0; i < H1_JPEG_QUANT_TABLE_COUNT; i++) {
		reg = get_unaligned_be32(&luma_qtable[i]);
		vepu_write_relaxed(vpu, reg, H1_REG_JPEG_LUMA_QUAT(i));

		reg = get_unaligned_be32(&chroma_qtable[i]);
		vepu_write_relaxed(vpu, reg, H1_REG_JPEG_CHROMA_QUAT(i));
	}
}