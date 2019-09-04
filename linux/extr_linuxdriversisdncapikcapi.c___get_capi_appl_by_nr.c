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
struct capi20_appl {int dummy; } ;

/* Variables and functions */
 int CAPI_MAXAPPL ; 
 struct capi20_appl** capi_applications ; 
 int /*<<< orphan*/  capi_controller_lock ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct capi20_appl *__get_capi_appl_by_nr(u16 applid)
{
	lockdep_assert_held(&capi_controller_lock);

	if (applid < 1 || applid - 1 >= CAPI_MAXAPPL)
		return NULL;

	return capi_applications[applid - 1];
}