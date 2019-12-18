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
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MUTEX_TRYLOCK_FAILED 130 
#define  MUTEX_TRYLOCK_RECURSIVE 129 
#define  MUTEX_TRYLOCK_SUCCESS 128 
 int mutex_trylock_recursive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool msm_gem_shrinker_lock(struct drm_device *dev, bool *unlock)
{
	/* NOTE: we are *closer* to being able to get rid of
	 * mutex_trylock_recursive().. the msm_gem code itself does
	 * not need struct_mutex, although codepaths that can trigger
	 * shrinker are still called in code-paths that hold the
	 * struct_mutex.
	 *
	 * Also, msm_obj->madv is protected by struct_mutex.
	 *
	 * The next step is probably split out a seperate lock for
	 * protecting inactive_list, so that shrinker does not need
	 * struct_mutex.
	 */
	switch (mutex_trylock_recursive(&dev->struct_mutex)) {
	case MUTEX_TRYLOCK_FAILED:
		return false;

	case MUTEX_TRYLOCK_SUCCESS:
		*unlock = true;
		return true;

	case MUTEX_TRYLOCK_RECURSIVE:
		*unlock = false;
		return true;
	}

	BUG();
}