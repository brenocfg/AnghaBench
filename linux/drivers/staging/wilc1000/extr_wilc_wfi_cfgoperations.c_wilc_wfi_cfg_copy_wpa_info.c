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
struct wilc_wfi_key {scalar_t__ key_len; scalar_t__ seq_len; int /*<<< orphan*/  cipher; void* seq; void* key; } ;
struct key_params {scalar_t__ key_len; scalar_t__ seq_len; int /*<<< orphan*/  cipher; int /*<<< orphan*/  seq; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_wfi_cfg_copy_wpa_info(struct wilc_wfi_key *key_info,
				      struct key_params *params)
{
	kfree(key_info->key);

	key_info->key = kmemdup(params->key, params->key_len, GFP_KERNEL);
	if (!key_info->key)
		return -ENOMEM;

	kfree(key_info->seq);

	if (params->seq_len > 0) {
		key_info->seq = kmemdup(params->seq, params->seq_len,
					GFP_KERNEL);
		if (!key_info->seq)
			return -ENOMEM;
	}

	key_info->cipher = params->cipher;
	key_info->key_len = params->key_len;
	key_info->seq_len = params->seq_len;

	return 0;
}