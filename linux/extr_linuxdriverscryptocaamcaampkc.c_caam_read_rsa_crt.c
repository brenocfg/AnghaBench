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

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  caam_rsa_drop_leading_zeros (int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/ * kzalloc (size_t,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static u8 *caam_read_rsa_crt(const u8 *ptr, size_t nbytes, size_t dstlen)
{
	u8 *dst;

	caam_rsa_drop_leading_zeros(&ptr, &nbytes);
	if (!nbytes)
		return NULL;

	dst = kzalloc(dstlen, GFP_DMA | GFP_KERNEL);
	if (!dst)
		return NULL;

	memcpy(dst + (dstlen - nbytes), ptr, nbytes);

	return dst;
}