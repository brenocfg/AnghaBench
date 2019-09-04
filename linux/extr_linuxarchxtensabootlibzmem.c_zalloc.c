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

/* Variables and functions */
 void* avail_ram ; 
 void* end_avail ; 
 int /*<<< orphan*/  exit () ; 

void *zalloc(unsigned size)
{
        void *p = avail_ram;

        size = (size + 7) & -8;
        avail_ram += size;
        if (avail_ram > end_avail) {
                //puts("oops... out of memory\n");
                //pause();
                exit ();
        }
        return p;
}