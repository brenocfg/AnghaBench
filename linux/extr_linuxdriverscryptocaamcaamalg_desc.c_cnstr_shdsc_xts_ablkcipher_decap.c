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
struct alginfo {int /*<<< orphan*/  algtype; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key_virt; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int CLASS_1 ; 
 int /*<<< orphan*/  FIFOLD_CLASS_SKIP ; 
 int HDR_SAVECTX ; 
 int HDR_SHARE_SERIAL ; 
 int JUMP_COND_SHRD ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_DEST_CLASS_REG ; 
 int LDST_CLASS_1_CCB ; 
 int LDST_OFFSET_SHIFT ; 
 int LDST_SRCDST_BYTE_CONTEXT ; 
 int /*<<< orphan*/  ablkcipher_append_src_dst (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  append_dec_op1 (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * append_jump (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  append_key_as_imm (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_load_as_imm (int /*<<< orphan*/ * const,void*,int,int) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int /*<<< orphan*/ * const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_load (int /*<<< orphan*/ * const,int,int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  init_sh_desc (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 

void cnstr_shdsc_xts_ablkcipher_decap(u32 * const desc, struct alginfo *cdata)
{
	__be64 sector_size = cpu_to_be64(512);
	u32 *key_jump_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);
	/* Skip if already shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	/* Load class1 key only */
	append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
			  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);

	/* Load sector size with index 40 bytes (0x28) */
	append_load_as_imm(desc, (void *)&sector_size, 8, LDST_CLASS_1_CCB |
			   LDST_SRCDST_BYTE_CONTEXT |
			   (0x28 << LDST_OFFSET_SHIFT));

	set_jump_tgt_here(desc, key_jump_cmd);

	/*
	 * create sequence for loading the sector index
	 * Upper 8B of IV - will be used as sector index
	 * Lower 8B of IV - will be discarded
	 */
	append_seq_load(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			(0x20 << LDST_OFFSET_SHIFT));
	append_seq_fifo_load(desc, 8, FIFOLD_CLASS_SKIP);

	/* Load operation */
	append_dec_op1(desc, cdata->algtype);

	/* Perform operation */
	ablkcipher_append_src_dst(desc);

#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "xts ablkcipher dec shdesc@" __stringify(__LINE__) ": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif
}