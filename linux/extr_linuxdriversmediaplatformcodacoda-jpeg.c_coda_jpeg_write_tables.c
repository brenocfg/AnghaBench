#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  struct coda_memcpy_desc {int member_0; int member_2; int /*<<< orphan*/  member_1; } const coda_memcpy_desc ;
struct TYPE_4__ {int /*<<< orphan*/  vaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * jpeg_qmat_tab; } ;
struct coda_ctx {TYPE_2__ parabuf; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  luma_dc_value ;
typedef  int /*<<< orphan*/  luma_dc_bits ;
typedef  int /*<<< orphan*/  luma_ac_value ;
typedef  int /*<<< orphan*/  luma_ac_bits ;
typedef  int /*<<< orphan*/  chroma_dc_value ;
typedef  int /*<<< orphan*/  chroma_dc_bits ;
typedef  int /*<<< orphan*/  chroma_ac_value ;
typedef  int /*<<< orphan*/  chroma_ac_bits ;

/* Variables and functions */
 int ARRAY_SIZE (struct coda_memcpy_desc const*) ; 
#define  chroma_ac_bits 135 
#define  chroma_ac_value 134 
#define  chroma_dc_bits 133 
#define  chroma_dc_value 132 
 int /*<<< orphan*/  coda_memcpy_parabuf (int /*<<< orphan*/ ,struct coda_memcpy_desc const*) ; 
#define  luma_ac_bits 131 
#define  luma_ac_value 130 
#define  luma_dc_bits 129 
#define  luma_dc_value 128 

int coda_jpeg_write_tables(struct coda_ctx *ctx)
{
	int i;
	static const struct coda_memcpy_desc huff[8] = {
		{ 0,   luma_dc_bits,    sizeof(luma_dc_bits)    },
		{ 16,  luma_dc_value,   sizeof(luma_dc_value)   },
		{ 32,  luma_ac_bits,    sizeof(luma_ac_bits)    },
		{ 48,  luma_ac_value,   sizeof(luma_ac_value)   },
		{ 216, chroma_dc_bits,  sizeof(chroma_dc_bits)  },
		{ 232, chroma_dc_value, sizeof(chroma_dc_value) },
		{ 248, chroma_ac_bits,  sizeof(chroma_ac_bits)  },
		{ 264, chroma_ac_value, sizeof(chroma_ac_value) },
	};
	struct coda_memcpy_desc qmat[3] = {
		{ 512, ctx->params.jpeg_qmat_tab[0], 64 },
		{ 576, ctx->params.jpeg_qmat_tab[1], 64 },
		{ 640, ctx->params.jpeg_qmat_tab[1], 64 },
	};

	/* Write huffman tables to parameter memory */
	for (i = 0; i < ARRAY_SIZE(huff); i++)
		coda_memcpy_parabuf(ctx->parabuf.vaddr, huff + i);

	/* Write Q-matrix to parameter memory */
	for (i = 0; i < ARRAY_SIZE(qmat); i++)
		coda_memcpy_parabuf(ctx->parabuf.vaddr, qmat + i);

	return 0;
}