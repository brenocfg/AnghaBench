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
typedef  int u32 ;
struct alginfo {int algtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAAM_CMD_SZ ; 
 int const CTR_RFC3686_IV_SIZE ; 
 int /*<<< orphan*/  DPOVRD ; 
 int FIFOLDST_VLF ; 
 int FIFOLD_CLASS_CLASS2 ; 
 int FIFOLD_TYPE_ICV ; 
 int FIFOLD_TYPE_LAST2 ; 
 int FIFOLD_TYPE_MSG ; 
 int FIFOST_TYPE_SKIP ; 
 int /*<<< orphan*/  IMM ; 
 int JUMP_COND_CALM ; 
 int JUMP_COND_NCP ; 
 int JUMP_COND_NIFP ; 
 int JUMP_COND_NIP ; 
 int JUMP_COND_NOP ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_VLF ; 
 int const LDST_CLASS_1_CCB ; 
 int LDST_CLASS_DECO ; 
 int const LDST_IMM ; 
 int LDST_OFFSET_SHIFT ; 
 int const LDST_SRCDST_BYTE_CONTEXT ; 
 int LDST_SRCDST_WORD_DECO_MATH3 ; 
 int const MOVE_DEST_CLASS2INFIFO ; 
 int const MOVE_OFFSET_SHIFT ; 
 int const MOVE_SRC_CLASS1CTX ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_ALG_DECRYPT ; 
 int OP_ALG_ICV_ON ; 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG3 ; 
 int /*<<< orphan*/  SEQOUTLEN ; 
 int /*<<< orphan*/  VARSEQINLEN ; 
 int /*<<< orphan*/  VARSEQOUTLEN ; 
 int /*<<< orphan*/  ZERO ; 
 int /*<<< orphan*/  aead_append_src_dst (int* const,int) ; 
 int /*<<< orphan*/  append_dec_op1 (int* const,int) ; 
 int* append_jump (int* const,int) ; 
 int /*<<< orphan*/  append_load_imm_be32 (int* const,int,int const) ; 
 int /*<<< orphan*/  append_math_add (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_math_add_imm_u32 (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  append_move (int* const,int const) ; 
 int /*<<< orphan*/  append_operation (int* const,int) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int* const,unsigned int,int) ; 
 int /*<<< orphan*/  append_seq_fifo_store (int* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_seq_load (int* const,unsigned int,int const) ; 
 int /*<<< orphan*/  init_sh_desc_key_aead (int* const,struct alginfo*,struct alginfo*,int const,int*,int) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int* const,int*) ; 

void cnstr_shdsc_aead_decap(u32 * const desc, struct alginfo *cdata,
			    struct alginfo *adata, unsigned int ivsize,
			    unsigned int icvsize, const bool geniv,
			    const bool is_rfc3686, u32 *nonce,
			    const u32 ctx1_iv_off, const bool is_qi, int era)
{
	/* Note: Context registers are saved. */
	init_sh_desc_key_aead(desc, cdata, adata, is_rfc3686, nonce, era);

	/* Class 2 operation */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_DECRYPT | OP_ALG_ICV_ON);

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

		if (!geniv)
			append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
					LDST_SRCDST_BYTE_CONTEXT |
					(ctx1_iv_off << LDST_OFFSET_SHIFT));
	}

	/* Read and write assoclen bytes */
	if (is_qi || era < 3) {
		append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
		if (geniv)
			append_math_add_imm_u32(desc, VARSEQOUTLEN, REG3, IMM,
						ivsize);
		else
			append_math_add(desc, VARSEQOUTLEN, ZERO, REG3,
					CAAM_CMD_SZ);
	} else {
		append_math_add(desc, VARSEQINLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
		if (geniv)
			append_math_add_imm_u32(desc, VARSEQOUTLEN, DPOVRD, IMM,
						ivsize);
		else
			append_math_add(desc, VARSEQOUTLEN, ZERO, DPOVRD,
					CAAM_CMD_SZ);
	}

	/* Skip assoc data */
	append_seq_fifo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* read assoc before reading payload */
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_CLASS2 | FIFOLD_TYPE_MSG |
			     KEY_VLF);

	if (geniv) {
		append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
				LDST_SRCDST_BYTE_CONTEXT |
				(ctx1_iv_off << LDST_OFFSET_SHIFT));
		append_move(desc, MOVE_SRC_CLASS1CTX | MOVE_DEST_CLASS2INFIFO |
			    (ctx1_iv_off << MOVE_OFFSET_SHIFT) | ivsize);
	}

	/* Load Counter into CONTEXT1 reg */
	if (is_rfc3686)
		append_load_imm_be32(desc, 1, LDST_IMM | LDST_CLASS_1_CCB |
				     LDST_SRCDST_BYTE_CONTEXT |
				     ((ctx1_iv_off + CTR_RFC3686_IV_SIZE) <<
				      LDST_OFFSET_SHIFT));

	/* Choose operation */
	if (ctx1_iv_off)
		append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
				 OP_ALG_DECRYPT);
	else
		append_dec_op1(desc, cdata->algtype);

	/* Read and write cryptlen bytes */
	append_math_add(desc, VARSEQINLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQOUTLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);
	aead_append_src_dst(desc, FIFOLD_TYPE_MSG);

	/* Load ICV */
	append_seq_fifo_load(desc, icvsize, FIFOLD_CLASS_CLASS2 |
			     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_ICV);

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "aead dec shdesc@" __stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif
}