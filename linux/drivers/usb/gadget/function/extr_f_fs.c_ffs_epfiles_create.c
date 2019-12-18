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
struct ffs_epfile {int /*<<< orphan*/  dentry; int /*<<< orphan*/  name; int /*<<< orphan*/  mutex; struct ffs_data* ffs; } ;
struct ffs_data {unsigned int eps_count; int user_flags; unsigned int* eps_addrmap; struct ffs_epfile* epfiles; int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ENTER () ; 
 int FUNCTIONFS_VIRTUAL_ADDR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ffs_epfile_operations ; 
 int /*<<< orphan*/  ffs_epfiles_destroy (struct ffs_epfile*,unsigned int) ; 
 int /*<<< orphan*/  ffs_sb_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ffs_epfile*,int /*<<< orphan*/ *) ; 
 struct ffs_epfile* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ffs_epfiles_create(struct ffs_data *ffs)
{
	struct ffs_epfile *epfile, *epfiles;
	unsigned i, count;

	ENTER();

	count = ffs->eps_count;
	epfiles = kcalloc(count, sizeof(*epfiles), GFP_KERNEL);
	if (!epfiles)
		return -ENOMEM;

	epfile = epfiles;
	for (i = 1; i <= count; ++i, ++epfile) {
		epfile->ffs = ffs;
		mutex_init(&epfile->mutex);
		if (ffs->user_flags & FUNCTIONFS_VIRTUAL_ADDR)
			sprintf(epfile->name, "ep%02x", ffs->eps_addrmap[i]);
		else
			sprintf(epfile->name, "ep%u", i);
		epfile->dentry = ffs_sb_create_file(ffs->sb, epfile->name,
						 epfile,
						 &ffs_epfile_operations);
		if (unlikely(!epfile->dentry)) {
			ffs_epfiles_destroy(epfiles, i - 1);
			return -ENOMEM;
		}
	}

	ffs->epfiles = epfiles;
	return 0;
}