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
 int __ecb3_crypt (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int,int) ; 

__attribute__((used)) static int ecb3_decrypt(struct blkcipher_desc *desc,
		       struct scatterlist *dst, struct scatterlist *src,
		       unsigned int nbytes)
{
	return __ecb3_crypt(desc, dst, src, nbytes, false);
}