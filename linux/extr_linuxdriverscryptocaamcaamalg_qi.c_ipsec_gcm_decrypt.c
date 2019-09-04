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
 int aead_crypt (struct aead_request*,int) ; 

__attribute__((used)) static int ipsec_gcm_decrypt(struct aead_request *req)
{
	if (req->assoclen < 8)
		return -EINVAL;

	return aead_crypt(req, false);
}