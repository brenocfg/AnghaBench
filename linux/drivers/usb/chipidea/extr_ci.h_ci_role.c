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
struct ci_role_driver {int dummy; } ;
struct ci_hdrc {size_t role; struct ci_role_driver** roles; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t CI_ROLE_END ; 

__attribute__((used)) static inline struct ci_role_driver *ci_role(struct ci_hdrc *ci)
{
	BUG_ON(ci->role >= CI_ROLE_END || !ci->roles[ci->role]);
	return ci->roles[ci->role];
}