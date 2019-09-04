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
 int CMD_LOAD ; 
 int DISABLE_AUTO_INFO_FIFO ; 
 int FIFOLD_CLASS_CLASS1 ; 
 int FIFOLD_CLASS_SKIP ; 
 int /*<<< orphan*/  FIFOLD_TYPE_AAD ; 
 int FIFOLD_TYPE_FLUSH1 ; 
 int FIFOLD_TYPE_IV ; 
 int /*<<< orphan*/  HDR_SHARE_SERIAL ; 
 int JUMP_COND_SHRD ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_DEST_CLASS_REG ; 
 int LDST_CLASS_1_CCB ; 
 int LDST_SRCDST_BYTE_CONTEXT ; 
 int MOVE_DEST_DESCBUF ; 
 int MOVE_DEST_MATH3 ; 
 int MOVE_DEST_OUTFIFO ; 
 int MOVE_LEN_SHIFT ; 
 int MOVE_SRC_DESCBUF ; 
 int MOVE_SRC_INFIFO_CL ; 
 int MOVE_SRC_MATH3 ; 
 int MOVE_WAITCOMP ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_ALG_ENCRYPT ; 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG3 ; 
 int /*<<< orphan*/  SEQINLEN ; 
 int /*<<< orphan*/  VARSEQINLEN ; 
 int /*<<< orphan*/  VARSEQOUTLEN ; 
 int /*<<< orphan*/  aead_append_src_dst (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_cmd (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_fifo_load_as_imm (int /*<<< orphan*/ * const,void*,int,int) ; 
 int /*<<< orphan*/ * append_jump (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_key (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  append_key_as_imm (int /*<<< orphan*/ * const,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  append_math_sub (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * append_move (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int /*<<< orphan*/ * const,unsigned int,int) ; 
 int /*<<< orphan*/  append_seq_store (int /*<<< orphan*/ * const,unsigned int,int) ; 
 int /*<<< orphan*/  init_sh_desc (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_move_tgt_here (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 

void cnstr_shdsc_rfc4543_encap(u32 * const desc, struct alginfo *cdata,
			       unsigned int ivsize, unsigned int icvsize,
			       const bool is_qi)
{
	u32 *key_jump_cmd, *read_move_cmd, *write_move_cmd;

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
		/* assoclen is not needed, skip it */
		append_seq_fifo_load(desc, 4, FIFOLD_CLASS_SKIP);

		/* Read salt and IV */
		append_fifo_load_as_imm(desc, (void *)(cdata->key_virt +
					cdata->keylen), 4, FIFOLD_CLASS_CLASS1 |
					FIFOLD_TYPE_IV);
		append_seq_fifo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);
	}

	/* assoclen + cryptlen = seqinlen */
	append_math_sub(desc, REG3, SEQINLEN, REG0, CAAM_CMD_SZ);

	/*
	 * MOVE_LEN opcode is not available in all SEC HW revisions,
	 * thus need to do some magic, i.e. self-patch the descriptor
	 * buffer.
	 */
	read_move_cmd = append_move(desc, MOVE_SRC_DESCBUF | MOVE_DEST_MATH3 |
				    (0x6 << MOVE_LEN_SHIFT));
	write_move_cmd = append_move(desc, MOVE_SRC_MATH3 | MOVE_DEST_DESCBUF |
				     (0x8 << MOVE_LEN_SHIFT) | MOVE_WAITCOMP);

	/* Will read assoclen + cryptlen bytes */
	append_math_sub(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Will write assoclen + cryptlen bytes */
	append_math_sub(desc, VARSEQOUTLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Read and write assoclen + cryptlen bytes */
	aead_append_src_dst(desc, FIFOLD_TYPE_AAD);

	set_move_tgt_here(desc, read_move_cmd);
	set_move_tgt_here(desc, write_move_cmd);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	/* Move payload data to OFIFO */
	append_move(desc, MOVE_SRC_INFIFO_CL | MOVE_DEST_OUTFIFO);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_1_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "rfc4543 enc shdesc@" __stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif
}