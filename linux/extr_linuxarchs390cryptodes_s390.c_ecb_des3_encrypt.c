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
struct blkcipher_walk {int dummy; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPACF_KM_TDEA_192 ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int ecb_desall_crypt (struct blkcipher_desc*,int /*<<< orphan*/ ,struct blkcipher_walk*) ; 

__attribute__((used)) static int ecb_des3_encrypt(struct blkcipher_desc *desc,
			    struct scatterlist *dst, struct scatterlist *src,
			    unsigned int nbytes)
{
	struct blkcipher_walk walk;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	return ecb_desall_crypt(desc, CPACF_KM_TDEA_192, &walk);
}