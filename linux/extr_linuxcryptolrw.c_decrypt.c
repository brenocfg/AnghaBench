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
 int /*<<< orphan*/  decrypt_done ; 
 int do_decrypt (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_crypt (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decrypt(struct skcipher_request *req)
{
	return do_decrypt(req, init_crypt(req, decrypt_done));
}