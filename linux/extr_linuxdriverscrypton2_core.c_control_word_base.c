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
typedef  int u64 ;

/* Variables and functions */
 int CONTROL_AUTH_TYPE_SHIFT ; 
 int CONTROL_ENCRYPT ; 
 int CONTROL_ENC_TYPE_SHIFT ; 
 int CONTROL_END_OF_BLOCK ; 
 int CONTROL_HASH_LEN_SHIFT ; 
 int CONTROL_HMAC_KEY_LEN_SHIFT ; 
 unsigned int CONTROL_LEN ; 
 int CONTROL_OPCODE_SHIFT ; 
 int CONTROL_START_OF_BLOCK ; 
 int CONTROL_STORE_FINAL_AUTH_STATE ; 

__attribute__((used)) static u64 control_word_base(unsigned int len, unsigned int hmac_key_len,
			     int enc_type, int auth_type,
			     unsigned int hash_len,
			     bool sfas, bool sob, bool eob, bool encrypt,
			     int opcode)
{
	u64 word = (len - 1) & CONTROL_LEN;

	word |= ((u64) opcode << CONTROL_OPCODE_SHIFT);
	word |= ((u64) enc_type << CONTROL_ENC_TYPE_SHIFT);
	word |= ((u64) auth_type << CONTROL_AUTH_TYPE_SHIFT);
	if (sfas)
		word |= CONTROL_STORE_FINAL_AUTH_STATE;
	if (sob)
		word |= CONTROL_START_OF_BLOCK;
	if (eob)
		word |= CONTROL_END_OF_BLOCK;
	if (encrypt)
		word |= CONTROL_ENCRYPT;
	if (hmac_key_len)
		word |= ((u64) (hmac_key_len - 1)) << CONTROL_HMAC_KEY_LEN_SHIFT;
	if (hash_len)
		word |= ((u64) (hash_len - 1)) << CONTROL_HASH_LEN_SHIFT;

	return word;
}