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
typedef  int /*<<< orphan*/  u32 ;
struct alginfo {int algtype; scalar_t__ keylen; scalar_t__ key_virt; int /*<<< orphan*/  key_dma; scalar_t__ key_inline; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAAM_CMD_SZ ; 
 int CLASS_1 ; 
 int FIFOLDST_VLF ; 
 int FIFOLD_CLASS_CLASS1 ; 
 int FIFOLD_CLASS_SKIP ; 
 int FIFOLD_TYPE_AAD ; 
 int FIFOLD_TYPE_FLUSH1 ; 
 int FIFOLD_TYPE_IV ; 
 int FIFOLD_TYPE_LAST1 ; 
 int FIFOLD_TYPE_MSG ; 
 int FIFOST_TYPE_MESSAGE_DATA ; 
 int FIFOST_TYPE_SKIP ; 
 int /*<<< orphan*/  HDR_SHARE_SERIAL ; 
 int /*<<< orphan*/  IMM ; 
 int JUMP_COND_CALM ; 
 int JUMP_COND_NCP ; 
 int JUMP_COND_NIFP ; 
 int JUMP_COND_NIP ; 
 int JUMP_COND_NOP ; 
 int JUMP_COND_SHRD ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_DEST_CLASS_REG ; 
 int LDST_CLASS_1_CCB ; 
 int LDST_CLASS_DECO ; 
 int LDST_OFFSET_SHIFT ; 
 int LDST_SRCDST_BYTE_CONTEXT ; 
 int LDST_SRCDST_WORD_DECO_MATH3 ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_ALG_ENCRYPT ; 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG3 ; 
 int /*<<< orphan*/  SEQINLEN ; 
 int /*<<< orphan*/  VARSEQINLEN ; 
 int /*<<< orphan*/  VARSEQOUTLEN ; 
 int /*<<< orphan*/  ZERO ; 
 int /*<<< orphan*/  append_fifo_load_as_imm (int /*<<< orphan*/ * const,void*,int,int) ; 
 int /*<<< orphan*/ * append_jump (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_key (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  append_key_as_imm (int /*<<< orphan*/ * const,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  append_math_add (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_math_sub (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_math_sub_imm_u32 (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int /*<<< orphan*/ * const,unsigned int,int) ; 
 int /*<<< orphan*/  append_seq_fifo_store (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_seq_load (int /*<<< orphan*/ * const,int,int) ; 
 int /*<<< orphan*/  append_seq_store (int /*<<< orphan*/ * const,unsigned int,int) ; 
 int /*<<< orphan*/  init_sh_desc (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 

void cnstr_shdsc_rfc4106_encap(u32 * const desc, struct alginfo *cdata,
			       unsigned int ivsize, unsigned int icvsize,
			       const bool is_qi)
{
	u32 *key_jump_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip key loading if it is loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	if (cdata->key_inline)
		append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
				  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	else
		append_key(desc, cdata->key_dma, cdata->keylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);
	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	if (is_qi) {
		u32 *wait_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		wait_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, wait_load_cmd);

		/* Read salt and IV */
		append_fifo_load_as_imm(desc, (void *)(cdata->key_virt +
					cdata->keylen), 4, FIFOLD_CLASS_CLASS1 |
					FIFOLD_TYPE_IV);
		append_seq_fifo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);
	}

	append_math_sub_imm_u32(desc, VARSEQINLEN, REG3, IMM, ivsize);
	append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);

	/* Read assoc data */
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_FLUSH1);

	/* Skip IV */
	append_seq_fifo_load(desc, ivsize, FIFOLD_CLASS_SKIP);

	/* Will read cryptlen bytes */
	append_math_sub(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Workaround for erratum A-005473 (simultaneous SEQ FIFO skips) */
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLD_TYPE_MSG);

	/* Skip assoc data */
	append_seq_fifo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* cryptlen = seqoutlen - assoclen */
	append_math_sub(desc, VARSEQOUTLEN, VARSEQINLEN, REG0, CAAM_CMD_SZ);

	/* Write encrypted data */
	append_seq_fifo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | FIFOLDST_VLF);

	/* Read payload data */
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_MSG | FIFOLD_TYPE_LAST1);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_1_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "rfc4106 enc shdesc@" __stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif
}