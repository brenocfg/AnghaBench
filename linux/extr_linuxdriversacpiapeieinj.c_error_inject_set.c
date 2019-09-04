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

/* Variables and functions */
 int EINVAL ; 
 int einj_error_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_flags ; 
 int /*<<< orphan*/  error_param1 ; 
 int /*<<< orphan*/  error_param2 ; 
 int /*<<< orphan*/  error_param3 ; 
 int /*<<< orphan*/  error_param4 ; 
 int /*<<< orphan*/  error_type ; 

__attribute__((used)) static int error_inject_set(void *data, u64 val)
{
	if (!error_type)
		return -EINVAL;

	return einj_error_inject(error_type, error_flags, error_param1, error_param2,
		error_param3, error_param4);
}