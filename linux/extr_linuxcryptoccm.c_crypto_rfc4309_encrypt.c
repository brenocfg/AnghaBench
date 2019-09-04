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
struct aead_request {int assoclen; } ;

/* Variables and functions */
 int EINVAL ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 struct aead_request* crypto_rfc4309_crypt (struct aead_request*) ; 

__attribute__((used)) static int crypto_rfc4309_encrypt(struct aead_request *req)
{
	if (req->assoclen != 16 && req->assoclen != 20)
		return -EINVAL;

	req = crypto_rfc4309_crypt(req);

	return crypto_aead_encrypt(req);
}