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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* memdup_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_ucm_alloc_data(const void **dest, u64 src, u32 len)
{
	void *data;

	*dest = NULL;

	if (!len)
		return 0;

	data = memdup_user(u64_to_user_ptr(src), len);
	if (IS_ERR(data))
		return PTR_ERR(data);

	*dest = data;
	return 0;
}