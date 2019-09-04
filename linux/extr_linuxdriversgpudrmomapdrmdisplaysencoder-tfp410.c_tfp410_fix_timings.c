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
struct videomode {int flags; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DE_HIGH ; 
 int DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int DISPLAY_FLAGS_SYNC_POSEDGE ; 

__attribute__((used)) static void tfp410_fix_timings(struct videomode *vm)
{
	vm->flags |= DISPLAY_FLAGS_DE_HIGH | DISPLAY_FLAGS_PIXDATA_POSEDGE |
		     DISPLAY_FLAGS_SYNC_POSEDGE;
}