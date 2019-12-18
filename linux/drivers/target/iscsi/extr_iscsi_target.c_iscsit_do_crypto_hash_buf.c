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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct scatterlist*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,void*,scalar_t__) ; 
 int /*<<< orphan*/  crypto_ahash_digest (struct ahash_request*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,void const*,scalar_t__) ; 

__attribute__((used)) static void iscsit_do_crypto_hash_buf(struct ahash_request *hash,
	const void *buf, u32 payload_length, u32 padding,
	const void *pad_bytes, void *data_crc)
{
	struct scatterlist sg[2];

	sg_init_table(sg, ARRAY_SIZE(sg));
	sg_set_buf(sg, buf, payload_length);
	if (padding)
		sg_set_buf(sg + 1, pad_bytes, padding);

	ahash_request_set_crypt(hash, sg, data_crc, payload_length + padding);

	crypto_ahash_digest(hash);
}