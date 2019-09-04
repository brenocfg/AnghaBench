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
struct akcipher_request {int dummy; } ;

/* Variables and functions */
 int ccp_rsa_crypt (struct akcipher_request*,int) ; 

__attribute__((used)) static int ccp_rsa_encrypt(struct akcipher_request *req)
{
	return ccp_rsa_crypt(req, true);
}