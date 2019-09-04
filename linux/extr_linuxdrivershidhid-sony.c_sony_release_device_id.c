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
struct sony_sc {int device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sony_device_id_allocator ; 

__attribute__((used)) static void sony_release_device_id(struct sony_sc *sc)
{
	if (sc->device_id >= 0) {
		ida_simple_remove(&sony_device_id_allocator, sc->device_id);
		sc->device_id = -1;
	}
}