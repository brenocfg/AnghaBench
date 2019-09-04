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
typedef  int /*<<< orphan*/  uuid_le ;

/* Variables and functions */
 int /*<<< orphan*/  null_guid ; 
 scalar_t__ uuid_le_cmp (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_null_guid(const uuid_le *guid)
{
	if (uuid_le_cmp(*guid, null_guid))
		return false;
	return true;
}