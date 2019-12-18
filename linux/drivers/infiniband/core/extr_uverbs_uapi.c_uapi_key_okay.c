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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ uapi_key_is_attr (int /*<<< orphan*/ ) ; 
 scalar_t__ uapi_key_is_ioctl_method (int /*<<< orphan*/ ) ; 
 scalar_t__ uapi_key_is_object (int /*<<< orphan*/ ) ; 
 scalar_t__ uapi_key_is_write_ex_method (int /*<<< orphan*/ ) ; 
 scalar_t__ uapi_key_is_write_method (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uapi_key_okay(u32 key)
{
	unsigned int count = 0;

	if (uapi_key_is_object(key))
		count++;
	if (uapi_key_is_ioctl_method(key))
		count++;
	if (uapi_key_is_write_method(key))
		count++;
	if (uapi_key_is_write_ex_method(key))
		count++;
	if (uapi_key_is_attr(key))
		count++;
	WARN(count != 1, "Bad count %d key=%x", count, key);
}