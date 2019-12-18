#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_rdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  MASTER_MINOR 129 
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
#define  SLAVE_MINOR 128 
 TYPE_2__* file_inode (struct file*) ; 
 int /*<<< orphan*/  fixed_size_llseek (struct file*,int /*<<< orphan*/ ,int,size_t) ; 
 TYPE_1__* image ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* type ; 
 size_t vme_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t vme_user_llseek(struct file *file, loff_t off, int whence)
{
	unsigned int minor = MINOR(file_inode(file)->i_rdev);
	size_t image_size;
	loff_t res;

	switch (type[minor]) {
	case MASTER_MINOR:
	case SLAVE_MINOR:
		mutex_lock(&image[minor].mutex);
		image_size = vme_get_size(image[minor].resource);
		res = fixed_size_llseek(file, off, whence, image_size);
		mutex_unlock(&image[minor].mutex);
		return res;
	}

	return -EINVAL;
}