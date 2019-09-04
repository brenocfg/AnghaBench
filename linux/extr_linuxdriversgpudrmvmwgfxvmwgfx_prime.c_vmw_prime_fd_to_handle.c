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
typedef  int /*<<< orphan*/  u32 ;
struct ttm_object_file {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct ttm_object_file* tfile; } ;

/* Variables and functions */
 int ttm_prime_fd_to_handle (struct ttm_object_file*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* vmw_fpriv (struct drm_file*) ; 

int vmw_prime_fd_to_handle(struct drm_device *dev,
			   struct drm_file *file_priv,
			   int fd, u32 *handle)
{
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;

	return ttm_prime_fd_to_handle(tfile, fd, handle);
}