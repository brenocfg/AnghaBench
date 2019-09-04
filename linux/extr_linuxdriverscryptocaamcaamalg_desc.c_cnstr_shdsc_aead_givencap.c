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
 int CMD_LOAD ; 
 int const CTR_RFC3686_IV_SIZE ; 
 int DISABLE_AUTO_INFO_FIFO ; 
 int /*<<< orphan*/  DPOVRD ; 
 int ENABLE_AUTO_INFO_FIFO ; 
 int FIFOLDST_VLF ; 
 int FIFOLD_CLASS_BOTH ; 
 int FIFOLD_CLASS_CLASS2 ; 
 int FIFOLD_CLASS_SKIP ; 
 int FIFOLD_TYPE_LASTBOTH ; 
 int FIFOLD_TYPE_MSG ; 
 int FIFOLD_TYPE_MSG1OUT2 ; 
 int FIFOST_TYPE_MESSAGE_DATA ; 
 int FIFOST_TYPE_SKIP ; 
 int JUMP_COND_CALM ; 
 int JUMP_COND_NCP ; 
 int JUMP_COND_NIFP ; 
 int JUMP_COND_NIP ; 
 int JUMP_COND_NOP ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_VLF ; 
 int const LDST_CLASS_1_CCB ; 
 int const LDST_CLASS_2_CCB ; 
 int LDST_CLASS_DECO ; 
 int const LDST_CLASS_IND_CCB ; 
 int const LDST_IMM ; 
 int LDST_OFFSET_SHIFT ; 
 int const LDST_SRCDST_BYTE_CONTEXT ; 
 int const LDST_SRCDST_WORD_DATASZ_REG ; 
 int LDST_SRCDST_WORD_DECO_MATH3 ; 
 int const LDST_SRCDST_WORD_INFO_FIFO ; 
 int const MOVE_DEST_CLASS1CTX ; 
 int const MOVE_DEST_OUTFIFO ; 
 unsigned int MOVE_LEN_SHIFT ; 
 int const MOVE_OFFSET_SHIFT ; 
 int const MOVE_SRC_CLASS1CTX ; 
 int const MOVE_SRC_INFIFO ; 
 int const MOVE_WAITCOMP ; 
 unsigned int NFIFOENTRY_DEST_CLASS2 ; 
 unsigned int NFIFOENTRY_DEST_DECO ; 
 unsigned int NFIFOENTRY_DLEN_SHIFT ; 
 unsigned int NFIFOENTRY_DTYPE_MSG ; 
 unsigned int NFIFOENTRY_LC1 ; 
 unsigned int NFIFOENTRY_PTYPE_RND ; 
 unsigned int NFIFOENTRY_STYPE_OFIFO ; 
 unsigned int NFIFOENTRY_STYPE_PAD ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_ALG_ENCRYPT ; 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG3 ; 
 int /*<<< orphan*/  SEQINLEN ; 
 int /*<<< orphan*/  VARSEQINLEN ; 
 int /*<<< orphan*/  VARSEQOUTLEN ; 
 int /*<<< orphan*/  ZERO ; 
 int /*<<< orphan*/  append_cmd (int* const,int) ; 
 int* append_jump (int* const,int) ; 
 int /*<<< orphan*/  append_load_imm_be32 (int* const,int,int const) ; 
 int /*<<< orphan*/  append_load_imm_u32 (int* const,unsigned int,int const) ; 
 int /*<<< orphan*/  append_math_add (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_move (int* const,int const) ; 
 int /*<<< orphan*/  append_operation (int* const,int) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int* const,unsigned int,int) ; 
 int /*<<< orphan*/  append_seq_fifo_store (int* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_seq_load (int* const,unsigned int,int const) ; 
 int /*<<< orphan*/  append_seq_store (int* const,unsigned int,int const) ; 
 int /*<<< orphan*/  init_sh_desc_key_aead (int* const,struct alginfo*,struct alginfo*,int const,int*,int) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int* const,int*) ; 

void cnstr_shdsc_aead_givencap(u32 * const desc, struct alginfo *cdata,
			       struct alginfo *adata, unsigned int ivsize,
			       unsigned int icvsize, const bool is_rfc3686,
			       u32 *nonce, const u32 ctx1_iv_off,
			       const bool is_qi, int era)
{
	u32 geniv, moveiv;

	/* Note: Context registers are saved. */
	init_sh_desc_key_aead(desc, cdata, adata, is_rfc3686, nonce, era);

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
	}

	if (is_rfc3686) {
		if (is_qi)
			append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
					LDST_SRCDST_BYTE_CONTEXT |
					(ctx1_iv_off << LDST_OFFSET_SHIFT));

		goto copy_iv;
	}

	/* Generate IV */
	geniv = NFIFOENTRY_STYPE_PAD | NFIFOENTRY_DEST_DECO |
		NFIFOENTRY_DTYPE_MSG | NFIFOENTRY_LC1 |
		NFIFOENTRY_PTYPE_RND | (ivsize << NFIFOENTRY_DLEN_SHIFT);
	append_load_imm_u32(desc, geniv, LDST_CLASS_IND_CCB |
			    LDST_SRCDST_WORD_INFO_FIFO | LDST_IMM);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	append_move(desc, MOVE_WAITCOMP |
		    MOVE_SRC_INFIFO | MOVE_DEST_CLASS1CTX |
		    (ctx1_iv_off << MOVE_OFFSET_SHIFT) |
		    (ivsize << MOVE_LEN_SHIFT));
	append_cmd(desc, CMD_LOAD | ENABLE_AUTO_INFO_FIFO);

copy_iv:
	/* Copy IV to class 1 context */
	append_move(desc, MOVE_SRC_CLASS1CTX | MOVE_DEST_OUTFIFO |
		    (ctx1_iv_off << MOVE_OFFSET_SHIFT) |
		    (ivsize << MOVE_LEN_SHIFT));

	/* Return to encryption */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	/* Read and write assoclen bytes */
	if (is_qi || era < 3) {
		append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);
	} else {
		append_math_add(desc, VARSEQINLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
	}

	/* Skip assoc data */
	append_seq_fifo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* read assoc before reading payload */
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_CLASS2 | FIFOLD_TYPE_MSG |
			     KEY_VLF);

	/* Copy iv from outfifo to class 2 fifo */
	moveiv = NFIFOENTRY_STYPE_OFIFO | NFIFOENTRY_DEST_CLASS2 |
		 NFIFOENTRY_DTYPE_MSG | (ivsize << NFIFOENTRY_DLEN_SHIFT);
	append_load_imm_u32(desc, moveiv, LDST_CLASS_IND_CCB |
			    LDST_SRCDST_WORD_INFO_FIFO | LDST_IMM);
	append_load_imm_u32(desc, ivsize, LDST_CLASS_2_CCB |
			    LDST_SRCDST_WORD_DATASZ_REG | LDST_IMM);

	/* Load Counter into CONTEXT1 reg */
	if (is_rfc3686)
		append_load_imm_be32(desc, 1, LDST_IMM | LDST_CLASS_1_CCB |
				     LDST_SRCDST_BYTE_CONTEXT |
				     ((ctx1_iv_off + CTR_RFC3686_IV_SIZE) <<
				      LDST_OFFSET_SHIFT));

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	/* Will write ivsize + cryptlen */
	append_math_add(desc, VARSEQOUTLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Not need to reload iv */
	append_seq_fifo_load(desc, ivsize,
			     FIFOLD_CLASS_SKIP);

	/* Will read cryptlen */
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_BOTH | KEY_VLF |
			     FIFOLD_TYPE_MSG1OUT2 | FIFOLD_TYPE_LASTBOTH);
	append_seq_fifo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | KEY_VLF);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "aead givenc shdesc@" __stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif
}