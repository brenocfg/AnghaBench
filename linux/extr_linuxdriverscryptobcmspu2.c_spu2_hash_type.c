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
typedef  enum hash_type { ____Placeholder_hash_type } hash_type ;

/* Variables and functions */
 int HASH_TYPE_FULL ; 

enum hash_type spu2_hash_type(u32 src_sent)
{
	return HASH_TYPE_FULL;
}