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
typedef  int uint64_t ;
struct error_descr {scalar_t__ type; int const mask; char* descr; } ;

/* Variables and functions */
 scalar_t__ ERR_CORRECTED ; 
 int snprintf (char*,size_t,char*,char*,char*) ; 

__attribute__((used)) static void decode_register(char *str, size_t size,
			   const struct error_descr *descr,
			   const uint64_t reg)
{
	int ret = 0;

	while (descr->type && descr->mask && descr->descr) {
		if (reg & descr->mask) {
			ret = snprintf(str, size, "\n\t%s, %s",
				       descr->type == ERR_CORRECTED ?
					 "Corrected" : "Uncorrected",
				       descr->descr);
			str += ret;
			size -= ret;
		}
		descr++;
	}
}