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
struct aes_ccm_nonce {int dummy; } ;
struct aes_ccm_label {int dummy; } ;

/* Variables and functions */
 int wusb_prf (void*,size_t,int /*<<< orphan*/  const*,struct aes_ccm_nonce const*,struct aes_ccm_label const*,void const*,size_t,int) ; 

__attribute__((used)) static inline int wusb_prf_128(void *out, size_t out_size, const u8 key[16],
			       const struct aes_ccm_nonce *n,
			       const struct aes_ccm_label *a,
			       const void *b, size_t blen)
{
	return wusb_prf(out, out_size, key, n, a, b, blen, 128);
}