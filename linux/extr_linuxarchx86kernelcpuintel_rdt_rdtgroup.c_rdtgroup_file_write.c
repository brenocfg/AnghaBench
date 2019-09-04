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
struct rftype {int /*<<< orphan*/  (* write ) (struct kernfs_open_file*,char*,size_t,int /*<<< orphan*/ ) ;} ;
struct kernfs_open_file {TYPE_1__* kn; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct rftype* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  stub1 (struct kernfs_open_file*,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t rdtgroup_file_write(struct kernfs_open_file *of, char *buf,
				   size_t nbytes, loff_t off)
{
	struct rftype *rft = of->kn->priv;

	if (rft->write)
		return rft->write(of, buf, nbytes, off);

	return -EINVAL;
}