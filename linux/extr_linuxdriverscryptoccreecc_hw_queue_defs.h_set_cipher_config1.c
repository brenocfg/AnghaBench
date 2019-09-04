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
struct cc_hw_desc {int /*<<< orphan*/ * word; } ;
typedef  enum cc_hash_conf_pad { ____Placeholder_cc_hash_conf_pad } cc_hash_conf_pad ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WORD4_CIPHER_CONF1 ; 

__attribute__((used)) static inline void set_cipher_config1(struct cc_hw_desc *pdesc,
				      enum cc_hash_conf_pad config)
{
	pdesc->word[4] |= FIELD_PREP(WORD4_CIPHER_CONF1, config);
}