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
typedef  int u16 ;
struct capi_ctr {int dummy; } ;

/* Variables and functions */
 int CAPI_MAXCONTR ; 
 struct capi_ctr** capi_controller ; 

__attribute__((used)) static inline struct capi_ctr *get_capi_ctr_by_nr(u16 contr)
{
	if (contr < 1 || contr - 1 >= CAPI_MAXCONTR)
		return NULL;

	return capi_controller[contr - 1];
}