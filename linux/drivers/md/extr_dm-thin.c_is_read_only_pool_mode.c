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
typedef  enum pool_mode { ____Placeholder_pool_mode } pool_mode ;

/* Variables and functions */
 int PM_OUT_OF_METADATA_SPACE ; 
 int PM_READ_ONLY ; 

__attribute__((used)) static bool is_read_only_pool_mode(enum pool_mode mode)
{
	return (mode == PM_OUT_OF_METADATA_SPACE || mode == PM_READ_ONLY);
}