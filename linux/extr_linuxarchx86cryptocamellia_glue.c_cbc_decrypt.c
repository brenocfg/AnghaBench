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
struct skcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  camellia_dec_cbc ; 
 int glue_cbc_decrypt_req_128bit (int /*<<< orphan*/ *,struct skcipher_request*) ; 

__attribute__((used)) static int cbc_decrypt(struct skcipher_request *req)
{
	return glue_cbc_decrypt_req_128bit(&camellia_dec_cbc, req);
}