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
typedef  int /*<<< orphan*/  u32 ;
struct secaeskeytoken {int dummy; } ;
struct pkey_seckey {int /*<<< orphan*/  seckey; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int cca_genseckey (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pkey_ccadata_aes_attr_read(u32 keytype, bool is_xts, char *buf,
					  loff_t off, size_t count)
{
	int rc;
	struct pkey_seckey *seckey = (struct pkey_seckey *) buf;

	if (off != 0 || count < sizeof(struct secaeskeytoken))
		return -EINVAL;
	if (is_xts)
		if (count < 2 * sizeof(struct secaeskeytoken))
			return -EINVAL;

	rc = cca_genseckey(-1, -1, keytype, seckey->seckey);
	if (rc)
		return rc;

	if (is_xts) {
		seckey++;
		rc = cca_genseckey(-1, -1, keytype, seckey->seckey);
		if (rc)
			return rc;

		return 2 * sizeof(struct secaeskeytoken);
	}

	return sizeof(struct secaeskeytoken);
}