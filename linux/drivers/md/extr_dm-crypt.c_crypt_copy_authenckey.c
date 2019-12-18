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
struct rtattr {int /*<<< orphan*/  rta_type; int /*<<< orphan*/  rta_len; } ;
struct crypto_authenc_key_param {int /*<<< orphan*/  enckeylen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_AUTHENC_KEYA_PARAM ; 
 struct crypto_authenc_key_param* RTA_DATA (struct rtattr*) ; 
 int /*<<< orphan*/  RTA_LENGTH (int) ; 
 int /*<<< orphan*/  RTA_SPACE (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,unsigned int) ; 

__attribute__((used)) static void crypt_copy_authenckey(char *p, const void *key,
				  unsigned enckeylen, unsigned authkeylen)
{
	struct crypto_authenc_key_param *param;
	struct rtattr *rta;

	rta = (struct rtattr *)p;
	param = RTA_DATA(rta);
	param->enckeylen = cpu_to_be32(enckeylen);
	rta->rta_len = RTA_LENGTH(sizeof(*param));
	rta->rta_type = CRYPTO_AUTHENC_KEYA_PARAM;
	p += RTA_SPACE(sizeof(*param));
	memcpy(p, key + enckeylen, authkeylen);
	p += authkeylen;
	memcpy(p, key, enckeylen);
}