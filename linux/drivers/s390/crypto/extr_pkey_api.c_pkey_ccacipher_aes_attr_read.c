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
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  enum pkey_key_size { ____Placeholder_pkey_key_size } pkey_key_size ;

/* Variables and functions */
 size_t CCACIPHERTOKENSIZE ; 
 int EINVAL ; 
 int cca_gencipherkey (int,int,int,int /*<<< orphan*/ ,char*,size_t*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t pkey_ccacipher_aes_attr_read(enum pkey_key_size keybits,
					    bool is_xts, char *buf, loff_t off,
					    size_t count)
{
	size_t keysize;
	int rc;

	if (off != 0 || count < CCACIPHERTOKENSIZE)
		return -EINVAL;
	if (is_xts)
		if (count < 2 * CCACIPHERTOKENSIZE)
			return -EINVAL;

	keysize = CCACIPHERTOKENSIZE;
	rc = cca_gencipherkey(-1, -1, keybits, 0, buf, &keysize);
	if (rc)
		return rc;
	memset(buf + keysize, 0, CCACIPHERTOKENSIZE - keysize);

	if (is_xts) {
		keysize = CCACIPHERTOKENSIZE;
		rc = cca_gencipherkey(-1, -1, keybits, 0,
				      buf + CCACIPHERTOKENSIZE, &keysize);
		if (rc)
			return rc;
		memset(buf + CCACIPHERTOKENSIZE + keysize, 0,
		       CCACIPHERTOKENSIZE - keysize);

		return 2 * CCACIPHERTOKENSIZE;
	}

	return CCACIPHERTOKENSIZE;
}