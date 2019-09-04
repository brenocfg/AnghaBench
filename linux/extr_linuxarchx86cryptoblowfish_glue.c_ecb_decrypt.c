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
 int /*<<< orphan*/  blowfish_dec_blk ; 
 int /*<<< orphan*/  blowfish_dec_blk_4way ; 
 int ecb_crypt (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecb_decrypt(struct skcipher_request *req)
{
	return ecb_crypt(req, blowfish_dec_blk, blowfish_dec_blk_4way);
}