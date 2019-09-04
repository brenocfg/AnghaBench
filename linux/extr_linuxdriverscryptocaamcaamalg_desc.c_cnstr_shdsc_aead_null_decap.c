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
struct alginfo {int algtype; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  keylen_pad; int /*<<< orphan*/  key_virt; scalar_t__ key_inline; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAAM_CMD_SZ ; 
 int CLASS_2 ; 
 int CMD_LOAD ; 
 int DISABLE_AUTO_INFO_FIFO ; 
 int ENABLE_AUTO_INFO_FIFO ; 
 int FIFOLD_CLASS_CLASS2 ; 
 int FIFOLD_TYPE_FLUSH1 ; 
 int FIFOLD_TYPE_ICV ; 
 int FIFOLD_TYPE_LAST2 ; 
 int FIFOLD_TYPE_MSG ; 
 int /*<<< orphan*/  HDR_SHARE_SERIAL ; 
 int JUMP_COND_SHRD ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_DEST_MDHA_SPLIT ; 
 int KEY_ENC ; 
 int MOVE_AUX_LS ; 
 int MOVE_DEST_DESCBUF ; 
 int MOVE_DEST_MATH2 ; 
 int MOVE_DEST_OUTFIFO ; 
 int MOVE_LEN_SHIFT ; 
 int MOVE_SRC_DESCBUF ; 
 int MOVE_SRC_INFIFO_CL ; 
 int MOVE_SRC_MATH2 ; 
 int MOVE_WAITCOMP ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_ALG_DECRYPT ; 
 int OP_ALG_ICV_ON ; 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG2 ; 
 int /*<<< orphan*/  SEQOUTLEN ; 
 int /*<<< orphan*/  VARSEQINLEN ; 
 int /*<<< orphan*/  VARSEQOUTLEN ; 
 int /*<<< orphan*/  ZERO ; 
 int /*<<< orphan*/  aead_append_src_dst (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_cmd (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/ * append_jump (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_key (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_key_as_imm (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_math_add (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_math_sub (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * append_move (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_proto_dkp (int /*<<< orphan*/ * const,struct alginfo*) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int /*<<< orphan*/ * const,unsigned int,int) ; 
 int /*<<< orphan*/  init_sh_desc (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_move_tgt_here (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 

void cnstr_shdsc_aead_null_decap(u32 * const desc, struct alginfo *adata,
				 unsigned int icvsize, int era)
{
	u32 *key_jump_cmd, *read_move_cmd, *write_move_cmd, *jump_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip if already shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	if (era < 6) {
		if (adata->key_inline)
			append_key_as_imm(desc, adata->key_virt,
					  adata->keylen_pad, adata->keylen,
					  CLASS_2 | KEY_DEST_MDHA_SPLIT |
					  KEY_ENC);
		else
			append_key(desc, adata->key_dma, adata->keylen,
				   CLASS_2 | KEY_DEST_MDHA_SPLIT | KEY_ENC);
	} else {
		append_proto_dkp(desc, adata);
	}
	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 2 operation */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_DECRYPT | OP_ALG_ICV_ON);

	/* assoclen + cryptlen = seqoutlen */
	append_math_sub(desc, REG2, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* Prepare to read and write cryptlen + assoclen bytes */
	append_math_add(desc, VARSEQINLEN, ZERO, REG2, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQOUTLEN, ZERO, REG2, CAAM_CMD_SZ);

	/*
	 * MOVE_LEN opcode is not available in all SEC HW revisions,
	 * thus need to do some magic, i.e. self-patch the descriptor
	 * buffer.
	 */
	read_move_cmd = append_move(desc, MOVE_SRC_DESCBUF |
				    MOVE_DEST_MATH2 |
				    (0x6 << MOVE_LEN_SHIFT));
	write_move_cmd = append_move(desc, MOVE_SRC_MATH2 |
				     MOVE_DEST_DESCBUF |
				     MOVE_WAITCOMP |
				     (0x8 << MOVE_LEN_SHIFT));

	/* Read and write cryptlen bytes */
	aead_append_src_dst(desc, FIFOLD_TYPE_MSG | FIFOLD_TYPE_FLUSH1);

	/*
	 * Insert a NOP here, since we need at least 4 instructions between
	 * code patching the descriptor buffer and the location being patched.
	 */
	jump_cmd = append_jump(desc, JUMP_TEST_ALL);
	set_jump_tgt_here(desc, jump_cmd);

	set_move_tgt_here(desc, read_move_cmd);
	set_move_tgt_here(desc, write_move_cmd);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	append_move(desc, MOVE_SRC_INFIFO_CL | MOVE_DEST_OUTFIFO |
		    MOVE_AUX_LS);
	append_cmd(desc, CMD_LOAD | ENABLE_AUTO_INFO_FIFO);

	/* Load ICV */
	append_seq_fifo_load(desc, icvsize, FIFOLD_CLASS_CLASS2 |
			     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_ICV);

#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "aead null dec shdesc@" __stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif
}