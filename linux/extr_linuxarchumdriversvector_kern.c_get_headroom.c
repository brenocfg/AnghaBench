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
struct arglist {int dummy; } ;

/* Variables and functions */
 int DEFAULT_HEADROOM ; 
 scalar_t__ kstrtoul (char*,int,long*) ; 
 char* uml_vector_fetch_arg (struct arglist*,char*) ; 

__attribute__((used)) static int get_headroom(struct arglist *def)
{
	char *mtu = uml_vector_fetch_arg(def, "headroom");
	long result;

	if (mtu != NULL) {
		if (kstrtoul(mtu, 10, &result) == 0)
			return result;
	}
	return DEFAULT_HEADROOM;
}