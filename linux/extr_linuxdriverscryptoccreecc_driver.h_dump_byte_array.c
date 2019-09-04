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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  __dump_byte_array (char const*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ cc_dump_bytes ; 

__attribute__((used)) static inline void dump_byte_array(const char *name, const u8 *the_array,
				   size_t size)
{
	if (cc_dump_bytes)
		__dump_byte_array(name, the_array, size);
}