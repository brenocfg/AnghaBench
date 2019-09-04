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
typedef  int umode_t ;
struct rftype {int mode; int /*<<< orphan*/  name; } ;
struct rdtgroup {int /*<<< orphan*/  kn; } ;
struct kernfs_node {int mode; } ;
struct iattr {int ia_mode; int /*<<< orphan*/  ia_valid; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rftype*) ; 
 int /*<<< orphan*/  ATTR_MODE ; 
 int ENOENT ; 
#define  KERNFS_DIR 130 
#define  KERNFS_FILE 129 
#define  KERNFS_LINK 128 
 int S_IFDIR ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 struct kernfs_node* kernfs_find_and_get_ns (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 struct kernfs_node* kernfs_get_parent (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int kernfs_setattr (struct kernfs_node*,struct iattr*) ; 
 int kernfs_type (struct kernfs_node*) ; 
 struct rftype* res_common_files ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int rdtgroup_kn_mode_restore(struct rdtgroup *r, const char *name,
			     umode_t mask)
{
	struct iattr iattr = {.ia_valid = ATTR_MODE,};
	struct kernfs_node *kn, *parent;
	struct rftype *rfts, *rft;
	int ret, len;

	rfts = res_common_files;
	len = ARRAY_SIZE(res_common_files);

	for (rft = rfts; rft < rfts + len; rft++) {
		if (!strcmp(rft->name, name))
			iattr.ia_mode = rft->mode & mask;
	}

	kn = kernfs_find_and_get_ns(r->kn, name, NULL);
	if (!kn)
		return -ENOENT;

	switch (kernfs_type(kn)) {
	case KERNFS_DIR:
		parent = kernfs_get_parent(kn);
		if (parent) {
			iattr.ia_mode |= parent->mode;
			kernfs_put(parent);
		}
		iattr.ia_mode |= S_IFDIR;
		break;
	case KERNFS_FILE:
		iattr.ia_mode |= S_IFREG;
		break;
	case KERNFS_LINK:
		iattr.ia_mode |= S_IFLNK;
		break;
	}

	ret = kernfs_setattr(kn, &iattr);
	kernfs_put(kn);
	return ret;
}