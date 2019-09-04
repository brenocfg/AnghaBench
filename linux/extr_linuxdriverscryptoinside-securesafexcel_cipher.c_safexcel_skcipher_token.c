#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_token {int stat; int instructions; int /*<<< orphan*/  packet_length; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {scalar_t__ token; int /*<<< orphan*/  options; } ;
struct safexcel_command_desc {TYPE_1__ control_data; } ;
struct safexcel_cipher_ctx {scalar_t__ mode; int alg; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_MODE_CBC ; 
 int DES3_EDE_BLOCK_SIZE ; 
 int DES_BLOCK_SIZE ; 
 int /*<<< orphan*/  EIP197_OPTION_2_TOKEN_IV_CMD ; 
 int /*<<< orphan*/  EIP197_OPTION_4_TOKEN_IV_CMD ; 
 int EIP197_TOKEN_INS_LAST ; 
 int EIP197_TOKEN_INS_TYPE_CRYTO ; 
 int EIP197_TOKEN_INS_TYPE_OUTPUT ; 
 int /*<<< orphan*/  EIP197_TOKEN_OPCODE_DIRECTION ; 
 int EIP197_TOKEN_STAT_LAST_HASH ; 
 int EIP197_TOKEN_STAT_LAST_PACKET ; 
#define  SAFEXCEL_3DES 130 
#define  SAFEXCEL_AES 129 
#define  SAFEXCEL_DES 128 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void safexcel_skcipher_token(struct safexcel_cipher_ctx *ctx, u8 *iv,
				    struct safexcel_command_desc *cdesc,
				    u32 length)
{
	struct safexcel_token *token;
	unsigned offset = 0;

	if (ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CBC) {
		switch (ctx->alg) {
		case SAFEXCEL_DES:
			offset = DES_BLOCK_SIZE / sizeof(u32);
			memcpy(cdesc->control_data.token, iv, DES_BLOCK_SIZE);
			cdesc->control_data.options |= EIP197_OPTION_2_TOKEN_IV_CMD;
			break;
		case SAFEXCEL_3DES:
			offset = DES3_EDE_BLOCK_SIZE / sizeof(u32);
			memcpy(cdesc->control_data.token, iv, DES3_EDE_BLOCK_SIZE);
			cdesc->control_data.options |= EIP197_OPTION_2_TOKEN_IV_CMD;
			break;

		case SAFEXCEL_AES:
			offset = AES_BLOCK_SIZE / sizeof(u32);
			memcpy(cdesc->control_data.token, iv, AES_BLOCK_SIZE);
			cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;
			break;
		}
	}

	token = (struct safexcel_token *)(cdesc->control_data.token + offset);

	token[0].opcode = EIP197_TOKEN_OPCODE_DIRECTION;
	token[0].packet_length = length;
	token[0].stat = EIP197_TOKEN_STAT_LAST_PACKET |
			EIP197_TOKEN_STAT_LAST_HASH;
	token[0].instructions = EIP197_TOKEN_INS_LAST |
				EIP197_TOKEN_INS_TYPE_CRYTO |
				EIP197_TOKEN_INS_TYPE_OUTPUT;
}