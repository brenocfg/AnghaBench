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
struct alginfo {unsigned int keylen; unsigned int keylen_pad; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key_virt; scalar_t__ key_inline; } ;

/* Variables and functions */
 int CLASS_1 ; 
 int CLASS_2 ; 
 unsigned int CTR_RFC3686_NONCE_SIZE ; 
 int HDR_SAVECTX ; 
 int HDR_SHARE_SERIAL ; 
 int JUMP_COND_SHRD ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_DEST_CLASS_REG ; 
 int KEY_DEST_MDHA_SPLIT ; 
 int KEY_ENC ; 
 int LDST_CLASS_IND_CCB ; 
 int LDST_IMM ; 
 int LDST_SRCDST_BYTE_OUTFIFO ; 
 int MOVE_DEST_CLASS1CTX ; 
 unsigned int MOVE_LEN_SHIFT ; 
 int MOVE_OFFSET_SHIFT ; 
 int MOVE_SRC_OUTFIFO ; 
 int /*<<< orphan*/ * append_jump (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_key (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  append_key_as_imm (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  append_load_as_imm (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  append_move (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_proto_dkp (int /*<<< orphan*/ * const,struct alginfo* const) ; 
 int /*<<< orphan*/  init_sh_desc (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_sh_desc_key_aead(u32 * const desc,
				  struct alginfo * const cdata,
				  struct alginfo * const adata,
				  const bool is_rfc3686, u32 *nonce, int era)
{
	u32 *key_jump_cmd;
	unsigned int enckeylen = cdata->keylen;

	/* Note: Context registers are saved. */
	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);

	/* Skip if already shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	/*
	 * RFC3686 specific:
	 *	| key = {AUTH_KEY, ENC_KEY, NONCE}
	 *	| enckeylen = encryption key size + nonce size
	 */
	if (is_rfc3686)
		enckeylen -= CTR_RFC3686_NONCE_SIZE;

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

	if (cdata->key_inline)
		append_key_as_imm(desc, cdata->key_virt, enckeylen,
				  enckeylen, CLASS_1 | KEY_DEST_CLASS_REG);
	else
		append_key(desc, cdata->key_dma, enckeylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);

	/* Load Counter into CONTEXT1 reg */
	if (is_rfc3686) {
		append_load_as_imm(desc, nonce, CTR_RFC3686_NONCE_SIZE,
				   LDST_CLASS_IND_CCB |
				   LDST_SRCDST_BYTE_OUTFIFO | LDST_IMM);
		append_move(desc,
			    MOVE_SRC_OUTFIFO |
			    MOVE_DEST_CLASS1CTX |
			    (16 << MOVE_OFFSET_SHIFT) |
			    (CTR_RFC3686_NONCE_SIZE << MOVE_LEN_SHIFT));
	}

	set_jump_tgt_here(desc, key_jump_cmd);
}