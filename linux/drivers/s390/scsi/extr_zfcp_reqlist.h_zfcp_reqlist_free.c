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
struct zfcp_reqlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct zfcp_reqlist*) ; 
 int /*<<< orphan*/  zfcp_reqlist_isempty (struct zfcp_reqlist*) ; 

__attribute__((used)) static inline void zfcp_reqlist_free(struct zfcp_reqlist *rl)
{
	/* sanity check */
	BUG_ON(!zfcp_reqlist_isempty(rl));

	kfree(rl);
}