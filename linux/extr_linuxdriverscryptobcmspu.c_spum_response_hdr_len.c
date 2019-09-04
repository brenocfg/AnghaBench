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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_HASH_RESP_HDR_LEN ; 
 int /*<<< orphan*/  SPU_RESP_HDR_LEN ; 

u16 spum_response_hdr_len(u16 auth_key_len, u16 enc_key_len, bool is_hash)
{
	if (is_hash)
		return SPU_HASH_RESP_HDR_LEN;
	else
		return SPU_RESP_HDR_LEN;
}