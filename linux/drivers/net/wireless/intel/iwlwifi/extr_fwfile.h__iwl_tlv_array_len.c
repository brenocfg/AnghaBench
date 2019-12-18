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
struct iwl_ucode_tlv {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (size_t) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t _iwl_tlv_array_len(const struct iwl_ucode_tlv *tlv,
					size_t fixed_size, size_t var_size)
{
	size_t var_len = le32_to_cpu(tlv->length) - fixed_size;

	if (WARN_ON(var_len % var_size))
		return 0;

	return var_len / var_size;
}