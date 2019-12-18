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
typedef  int /*<<< orphan*/  u16 ;
struct pasid_entry {int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16
pasid_get_domain_id(struct pasid_entry *pe)
{
	return (u16)(READ_ONCE(pe->val[1]) & GENMASK_ULL(15, 0));
}