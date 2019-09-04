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
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int current_device ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z2ram_mutex ; 

__attribute__((used)) static void
z2_release(struct gendisk *disk, fmode_t mode)
{
    mutex_lock(&z2ram_mutex);
    if ( current_device == -1 ) {
    	mutex_unlock(&z2ram_mutex);
    	return;
    }
    mutex_unlock(&z2ram_mutex);
    /*
     * FIXME: unmap memory
     */
}