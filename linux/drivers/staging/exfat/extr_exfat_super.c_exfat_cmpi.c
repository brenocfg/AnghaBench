#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qstr {int /*<<< orphan*/  name; } ;
struct nls_table {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct nls_table* nls_io; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (int /*<<< orphan*/ ) ; 
 unsigned int __exfat_striptail_len (unsigned int,char const*) ; 
 unsigned int exfat_striptail_len (struct qstr const*) ; 
 scalar_t__ nls_strnicmp (struct nls_table*,int /*<<< orphan*/ ,char const*,unsigned int) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static int exfat_cmpi(const struct dentry *dentry, unsigned int len,
		      const char *str, const struct qstr *name)
{
	struct nls_table *t = EXFAT_SB(dentry->d_sb)->nls_io;
	unsigned int alen, blen;

	alen = exfat_striptail_len(name);
	blen = __exfat_striptail_len(len, str);
	if (alen == blen) {
		if (!t) {
			if (strncasecmp(name->name, str, alen) == 0)
				return 0;
		} else {
			if (nls_strnicmp(t, name->name, str, alen) == 0)
				return 0;
		}
	}
	return 1;
}