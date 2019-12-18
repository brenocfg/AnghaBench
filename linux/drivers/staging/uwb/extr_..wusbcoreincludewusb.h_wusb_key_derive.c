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
struct wusb_keydvt_out {int dummy; } ;
struct wusb_keydvt_in {int dummy; } ;
struct aes_ccm_nonce {int dummy; } ;
struct aes_ccm_label {char* data; } ;

/* Variables and functions */
 int wusb_prf_256 (struct wusb_keydvt_out*,int,int /*<<< orphan*/  const*,struct aes_ccm_nonce const*,struct aes_ccm_label const*,struct wusb_keydvt_in const*,int) ; 

__attribute__((used)) static inline int wusb_key_derive(struct wusb_keydvt_out *keydvt_out,
				  const u8 key[16],
				  const struct aes_ccm_nonce *n,
				  const struct wusb_keydvt_in *keydvt_in)
{
	const struct aes_ccm_label a = { .data = "Pair-wise keys" };
	return wusb_prf_256(keydvt_out, sizeof(*keydvt_out), key, n, &a,
			    keydvt_in, sizeof(*keydvt_in));
}