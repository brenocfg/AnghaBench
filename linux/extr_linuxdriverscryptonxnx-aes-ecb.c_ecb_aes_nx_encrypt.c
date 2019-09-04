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
struct scatterlist {int dummy; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 int ecb_aes_nx_crypt (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int,int) ; 

__attribute__((used)) static int ecb_aes_nx_encrypt(struct blkcipher_desc *desc,
			      struct scatterlist    *dst,
			      struct scatterlist    *src,
			      unsigned int           nbytes)
{
	return ecb_aes_nx_crypt(desc, dst, src, nbytes, 1);
}