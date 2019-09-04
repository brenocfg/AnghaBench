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
 int sec_alg_skcipher_crypto (struct skcipher_request*,int) ; 

__attribute__((used)) static int sec_alg_skcipher_encrypt(struct skcipher_request *req)
{
	return sec_alg_skcipher_crypto(req, true);
}