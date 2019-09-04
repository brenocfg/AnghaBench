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
struct cc_hw_desc {int* word; } ;
typedef  enum cc_hw_crypto_key { ____Placeholder_cc_hw_crypto_key } cc_hw_crypto_key ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int HW_KEY_MASK_CIPHER_DO ; 
 int HW_KEY_SHIFT_CIPHER_CFG2 ; 
 int /*<<< orphan*/  WORD4_CIPHER_CONF2 ; 
 int /*<<< orphan*/  WORD4_CIPHER_DO ; 

__attribute__((used)) static inline void set_hw_crypto_key(struct cc_hw_desc *pdesc,
				     enum cc_hw_crypto_key hw_key)
{
	pdesc->word[4] |= FIELD_PREP(WORD4_CIPHER_DO,
				     (hw_key & HW_KEY_MASK_CIPHER_DO)) |
			FIELD_PREP(WORD4_CIPHER_CONF2,
				   (hw_key >> HW_KEY_SHIFT_CIPHER_CFG2));
}