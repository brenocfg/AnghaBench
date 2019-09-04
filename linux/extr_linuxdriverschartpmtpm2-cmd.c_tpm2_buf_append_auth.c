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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct tpm_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpm_buf_append (struct tpm_buf*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  tpm_buf_append_u16 (struct tpm_buf*,scalar_t__) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,scalar_t__) ; 
 int /*<<< orphan*/  tpm_buf_append_u8 (struct tpm_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tpm2_buf_append_auth(struct tpm_buf *buf, u32 session_handle,
				 const u8 *nonce, u16 nonce_len,
				 u8 attributes,
				 const u8 *hmac, u16 hmac_len)
{
	tpm_buf_append_u32(buf, 9 + nonce_len + hmac_len);
	tpm_buf_append_u32(buf, session_handle);
	tpm_buf_append_u16(buf, nonce_len);

	if (nonce && nonce_len)
		tpm_buf_append(buf, nonce, nonce_len);

	tpm_buf_append_u8(buf, attributes);
	tpm_buf_append_u16(buf, hmac_len);

	if (hmac && hmac_len)
		tpm_buf_append(buf, hmac, hmac_len);
}