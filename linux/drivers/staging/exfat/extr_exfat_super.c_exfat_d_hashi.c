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
struct super_block {int dummy; } ;
struct qstr {unsigned char* name; int /*<<< orphan*/  hash; } ;
struct dentry {struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned int exfat_striptail_len (struct qstr*) ; 
 unsigned long init_name_hash (struct dentry const*) ; 
 int /*<<< orphan*/  nls_upper (struct super_block*,int /*<<< orphan*/ ) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int exfat_d_hashi(const struct dentry *dentry, struct qstr *qstr)
{
	struct super_block *sb = dentry->d_sb;
	const unsigned char *name;
	unsigned int len;
	unsigned long hash;

	name = qstr->name;
	len = exfat_striptail_len(qstr);

	hash = init_name_hash(dentry);
	while (len--)
		hash = partial_name_hash(nls_upper(sb, *name++), hash);
	qstr->hash = end_name_hash(hash);

	return 0;
}